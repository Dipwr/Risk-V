module uart #(
	parameter int CLK_FREQ      = 25_000_000,
	parameter int BAUD          = 115_200,
	parameter int RX_FIFO_DEPTH = 64, // must be power of 2 (>= 2)
	parameter int TX_FIFO_DEPTH = 64  // must be power of 2 (>= 2)
)(
	input  logic        clk,
	input  logic        rst,

	//bus interface
	input  logic        we,
	input  logic        re,
	input  logic [3:0]  addr,
	input  logic [31:0] wdata,
	output logic [31:0] rdata,

	//serial pins
	input  logic        rx,
	output logic        tx,

	//interrupt status
	output logic        rx_avail
);
	localparam int          CLKS_PER_BIT = CLK_FREQ / BAUD;
	localparam logic [15:0] HALF_BIT_CNT = 16'((CLKS_PER_BIT / 2) - 1);
	localparam logic [15:0] FULL_BIT_CNT = 16'(CLKS_PER_BIT - 1);

	localparam int RX_PTR_W = $clog2(RX_FIFO_DEPTH);
	localparam int TX_PTR_W = $clog2(TX_FIFO_DEPTH);

	localparam logic [RX_PTR_W-1:0] RX_PTR_ONE   = {{(RX_PTR_W-1){1'b0}}, 1'b1};
	localparam logic [RX_PTR_W:0]   RX_CNT_ONE   = {{RX_PTR_W{1'b0}}, 1'b1};
	localparam logic [RX_PTR_W:0]   RX_DEPTH_MAX = {1'b1, {RX_PTR_W{1'b0}}};

	localparam logic [TX_PTR_W-1:0] TX_PTR_ONE   = {{(TX_PTR_W-1){1'b0}}, 1'b1};
	localparam logic [TX_PTR_W:0]   TX_CNT_ONE   = {{TX_PTR_W{1'b0}}, 1'b1};
	localparam logic [TX_PTR_W:0]   TX_DEPTH_MAX = {1'b1, {TX_PTR_W{1'b0}}};

	//2-ff rx synchronizer to prevent metastability
	(* ASYNC_REG = "TRUE" *) logic rx_sync_1;
	(* ASYNC_REG = "TRUE" *) logic rx_sync_2;
	always_ff @(posedge clk) begin
		if (rst) begin
			rx_sync_1 <= 1'b1;
			rx_sync_2 <= 1'b1;
		end else begin
			rx_sync_1 <= rx;
			rx_sync_2 <= rx_sync_1;
		end
	end

	//rx state machine (isolated shift register)
	typedef enum logic [2:0] {RX_IDLE, RX_START, RX_DATA, RX_STOP, RX_WAIT_IDLE} rx_state_t;
	rx_state_t rx_state;

	logic [15:0] rx_clk_cnt;
	logic [2:0]  rx_bit_idx;
	logic [7:0]  rx_shift_reg;

	always_ff @(posedge clk) begin
		if (rst) begin
			rx_state     <= RX_IDLE;
			rx_clk_cnt   <= 16'd0;
			rx_bit_idx   <= 3'd0;
			rx_shift_reg <= 8'd0;
		end else begin
			case (rx_state)
				RX_IDLE: begin
					rx_clk_cnt <= 16'd0;
					rx_bit_idx <= 3'd0;
					if (rx_sync_2 == 1'b0) begin
						rx_state <= RX_START;
					end
				end

				RX_START: begin
					//sample at middle of start bit
					if (rx_clk_cnt == HALF_BIT_CNT) begin
						rx_clk_cnt <= 16'd0;
						if (rx_sync_2 == 1'b0) begin
							rx_bit_idx <= 3'd0;
							rx_state   <= RX_DATA;
						end else begin
							rx_state   <= RX_IDLE;
						end
					end else begin
						rx_clk_cnt <= rx_clk_cnt + 16'd1;
					end
				end

				RX_DATA: begin
					if (rx_clk_cnt == FULL_BIT_CNT) begin
						rx_clk_cnt               <= 16'd0;
						rx_shift_reg[rx_bit_idx] <= rx_sync_2;
						if (rx_bit_idx == 3'd7) begin
							rx_state <= RX_STOP;
						end else begin
							rx_bit_idx <= rx_bit_idx + 3'd1;
						end
					end else begin
						rx_clk_cnt <= rx_clk_cnt + 16'd1;
					end
				end

				RX_STOP: begin
					//verify stop bit before committing byte; wait for line idle on break/framing error
					if (rx_clk_cnt == FULL_BIT_CNT) begin
						rx_clk_cnt <= 16'd0;
						if (rx_sync_2 == 1'b1) begin
							rx_state <= RX_IDLE;
						end else begin
							rx_state <= RX_WAIT_IDLE;
						end
					end else begin
						rx_clk_cnt <= rx_clk_cnt + 16'd1;
					end
				end

				RX_WAIT_IDLE: begin
					if (rx_sync_2 == 1'b1) begin
						rx_state <= RX_IDLE;
					end
				end

				default: rx_state <= RX_IDLE;
			endcase
		end
	end

	//rx circular fifo & sticky status error flags
	logic [7:0]          rx_fifo_mem [0:RX_FIFO_DEPTH-1];
	logic [RX_PTR_W-1:0] rx_wr_ptr, rx_rd_ptr;
	logic [RX_PTR_W:0]   rx_count;
	logic                rx_overrun, rx_framing_err;

	logic       rx_empty, rx_full;
	logic       rx_push_req, rx_pop_req, rx_flush_req;
	logic       rx_do_push, rx_overrun_evt, rx_framing_evt;
	logic [7:0] rx_head_byte;

	assign rx_empty       = (rx_count == '0);
	assign rx_avail       = ~rx_empty;
	assign rx_full        = (rx_count == RX_DEPTH_MAX);
	assign rx_push_req    = (rx_state == RX_STOP) && (rx_clk_cnt == FULL_BIT_CNT) && (rx_sync_2 == 1'b1);
	assign rx_pop_req     = re && (addr == 4'h0) && !rx_empty;
	assign rx_flush_req   = we && (addr == 4'h4) && wdata[4];
	assign rx_do_push     = rx_push_req && !rx_flush_req && (!rx_full || rx_pop_req);
	assign rx_overrun_evt = rx_push_req && !rx_flush_req && rx_full && !rx_pop_req;
	assign rx_framing_evt = (rx_state == RX_STOP) && (rx_clk_cnt == FULL_BIT_CNT) && (rx_sync_2 == 1'b0);
	assign rx_head_byte   = rx_empty ? 8'd0 : rx_fifo_mem[rx_rd_ptr];

	//keep fifo array without reset so vivado infers distributed lutram
	always_ff @(posedge clk) begin
		if (rx_do_push) begin
			rx_fifo_mem[rx_wr_ptr] <= rx_shift_reg;
		end
	end

	always_ff @(posedge clk) begin
		if (rst) begin
			rx_wr_ptr <= '0;
			rx_rd_ptr <= '0;
			rx_count  <= '0;
		end else if (rx_flush_req) begin
			rx_wr_ptr <= '0;
			rx_rd_ptr <= '0;
			rx_count  <= '0;
		end else begin
			if (rx_do_push) begin
				rx_wr_ptr <= rx_wr_ptr + RX_PTR_ONE;
			end
			if (rx_pop_req) begin
				rx_rd_ptr <= rx_rd_ptr + RX_PTR_ONE;
			end
			case ({rx_do_push, rx_pop_req})
				2'b10:   rx_count <= rx_count + RX_CNT_ONE;
				2'b01:   rx_count <= rx_count - RX_CNT_ONE;
				default: rx_count <= rx_count;
			endcase
		end
	end

	always_ff @(posedge clk) begin
		if (rst) begin
			rx_overrun     <= 1'b0;
			rx_framing_err <= 1'b0;
		end else begin
			if (we && (addr == 4'h4) && wdata[2]) begin
				rx_overrun <= 1'b0;
			end
			if (we && (addr == 4'h4) && wdata[3]) begin
				rx_framing_err <= 1'b0;
			end
			//same-cycle error event overrides w1c clear
			if (rx_overrun_evt) begin
				rx_overrun <= 1'b1;
			end
			if (rx_framing_evt) begin
				rx_framing_err <= 1'b1;
			end
		end
	end

	//tx circular fifo & tx state machine
	typedef enum logic [1:0] {TX_IDLE, TX_START, TX_DATA, TX_STOP} tx_state_t;
	tx_state_t tx_state;

	logic [7:0]          tx_fifo_mem [0:TX_FIFO_DEPTH-1];
	logic [TX_PTR_W-1:0] tx_wr_ptr, tx_rd_ptr;
	logic [TX_PTR_W:0]   tx_count;
	logic [15:0]         tx_clk_cnt;
	logic [2:0]          tx_bit_idx;
	logic [7:0]          tx_shift_reg;

	logic tx_empty, tx_full, tx_push_req, tx_pop_req, tx_idle;

	assign tx_empty    = (tx_count == '0);
	assign tx_full     = (tx_count == TX_DEPTH_MAX);
	assign tx_push_req = we && (addr == 4'h0) && !tx_full;
	assign tx_pop_req  = (tx_state == TX_IDLE) && !tx_empty;
	assign tx_idle     = tx_empty && (tx_state == TX_IDLE);

	always_ff @(posedge clk) begin
		if (tx_push_req) begin
			tx_fifo_mem[tx_wr_ptr] <= wdata[7:0];
		end
	end

	always_ff @(posedge clk) begin
		if (rst) begin
			tx_wr_ptr <= '0;
			tx_rd_ptr <= '0;
			tx_count  <= '0;
		end else begin
			if (tx_push_req) begin
				tx_wr_ptr <= tx_wr_ptr + TX_PTR_ONE;
			end
			if (tx_pop_req) begin
				tx_rd_ptr <= tx_rd_ptr + TX_PTR_ONE;
			end
			case ({tx_push_req, tx_pop_req})
				2'b10:   tx_count <= tx_count + TX_CNT_ONE;
				2'b01:   tx_count <= tx_count - TX_CNT_ONE;
				default: tx_count <= tx_count;
			endcase
		end
	end

	always_ff @(posedge clk) begin
		if (rst) begin
			tx_state     <= TX_IDLE;
			tx_clk_cnt   <= 16'd0;
			tx_bit_idx   <= 3'd0;
			tx_shift_reg <= 8'd0;
			tx           <= 1'b1;
		end else begin
			case (tx_state)
				TX_IDLE: begin
					tx         <= 1'b1;
					tx_clk_cnt <= 16'd0;
					if (!tx_empty) begin
						tx_shift_reg <= tx_fifo_mem[tx_rd_ptr];
						tx_state     <= TX_START;
					end
				end

				TX_START: begin
					tx <= 1'b0; // start bit
					if (tx_clk_cnt == FULL_BIT_CNT) begin
						tx_clk_cnt <= 16'd0;
						tx_bit_idx <= 3'd0;
						tx_state   <= TX_DATA;
					end else begin
						tx_clk_cnt <= tx_clk_cnt + 16'd1;
					end
				end

				TX_DATA: begin
					tx <= tx_shift_reg[tx_bit_idx];
					if (tx_clk_cnt == FULL_BIT_CNT) begin
						tx_clk_cnt <= 16'd0;
						if (tx_bit_idx == 3'd7) begin
							tx_state <= TX_STOP;
						end else begin
							tx_bit_idx <= tx_bit_idx + 3'd1;
						end
					end else begin
						tx_clk_cnt <= tx_clk_cnt + 16'd1;
					end
				end

				TX_STOP: begin
					tx <= 1'b1; // stop bit
					if (tx_clk_cnt == FULL_BIT_CNT) begin
						tx_clk_cnt <= 16'd0;
						tx_state   <= TX_IDLE;
					end else begin
						tx_clk_cnt <= tx_clk_cnt + 16'd1;
					end
				end

				default: begin
					tx       <= 1'b1;
					tx_state <= TX_IDLE;
				end
			endcase
		end
	end

	//status register (0x4):
	//  [0] rx_ready (~rx_empty)
	//  [1] tx_ready (~tx_full)
	//  [2] rx_overrun (w1c)
	//  [3] rx_framing_err (w1c)
	//  [4] tx_idle (r) / rx_fifo_flush (w1)
	assign rdata = (addr == 4'h0) ? {24'd0, rx_head_byte} :
	               (addr == 4'h4) ? {27'd0, tx_idle, rx_framing_err, rx_overrun, ~tx_full, ~rx_empty} :
	               32'd0;

endmodule
