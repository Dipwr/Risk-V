module uart #(
	parameter int CLK_FREQ = 25_000_000,
	parameter int BAUD     = 115_200
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
	output logic        tx
);
	localparam int CLKS_PER_BIT = CLK_FREQ / BAUD; // 217 at 25 mhz

	//2-ff rx synchronizer to prevent metastability
	logic rx_sync_1, rx_sync_2;
	always_ff @(posedge clk or posedge rst) begin
		if (rst) begin
			rx_sync_1 <= 1'b1;
			rx_sync_2 <= 1'b1;
		end else begin
			rx_sync_1 <= rx;
			rx_sync_2 <= rx_sync_1;
		end
	end

	//rx state machine
	typedef enum logic [1:0] {RX_IDLE, RX_START, RX_DATA, RX_STOP} rx_state_t;
	rx_state_t rx_state;

	logic [15:0] rx_clk_cnt;
	logic [2:0]  rx_bit_idx;
	logic [7:0]  rx_data_reg;
	logic        rx_ready;

	always_ff @(posedge clk or posedge rst) begin
		if (rst) begin
			rx_state    <= RX_IDLE;
			rx_clk_cnt  <= 16'd0;
			rx_bit_idx  <= 3'd0;
			rx_data_reg <= 8'd0;
			rx_ready    <= 1'b0;
		end else begin
			//clear rx_ready when cpu reads data register (addr 0x00)
			if (re && (addr == 4'h0)) begin
				rx_ready <= 1'b0;
			end

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
					if (rx_clk_cnt == (CLKS_PER_BIT / 2)) begin
						if (rx_sync_2 == 1'b0) begin
							rx_clk_cnt <= 16'd0;
							rx_state   <= RX_DATA;
						end else begin
							rx_state <= RX_IDLE;
						end
					end else begin
						rx_clk_cnt <= rx_clk_cnt + 16'd1;
					end
				end

				RX_DATA: begin
					if (rx_clk_cnt == (CLKS_PER_BIT - 1)) begin
						rx_clk_cnt            <= 16'd0;
						rx_data_reg[rx_bit_idx] <= rx_sync_2;
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
					if (rx_clk_cnt == (CLKS_PER_BIT - 1)) begin
						rx_ready <= 1'b1;
						rx_state <= RX_IDLE;
					end else begin
						rx_clk_cnt <= rx_clk_cnt + 16'd1;
					end
				end
			endcase
		end
	end

	//tx state machine
	typedef enum logic [1:0] {TX_IDLE, TX_START, TX_DATA, TX_STOP} tx_state_t;
	tx_state_t tx_state;

	logic [15:0] tx_clk_cnt;
	logic [2:0]  tx_bit_idx;
	logic [7:0]  tx_data_reg;
	logic        tx_busy;

	always_ff @(posedge clk or posedge rst) begin
		if (rst) begin
			tx_state    <= TX_IDLE;
			tx_clk_cnt  <= 16'd0;
			tx_bit_idx  <= 3'd0;
			tx_data_reg <= 8'd0;
			tx          <= 1'b1;
			tx_busy     <= 1'b0;
		end else begin
			case (tx_state)
				TX_IDLE: begin
					tx      <= 1'b1;
					tx_busy <= 1'b0;
					if (we && (addr == 4'h0)) begin
						tx_data_reg <= wdata[7:0];
						tx_busy     <= 1'b1;
						tx_clk_cnt  <= 16'd0;
						tx_state    <= TX_START;
					end
				end

				TX_START: begin
					tx <= 1'b0; // start bit
					if (tx_clk_cnt == (CLKS_PER_BIT - 1)) begin
						tx_clk_cnt <= 16'd0;
						tx_bit_idx <= 3'd0;
						tx_state   <= TX_DATA;
					end else begin
						tx_clk_cnt <= tx_clk_cnt + 16'd1;
					end
				end

				TX_DATA: begin
					tx <= tx_data_reg[tx_bit_idx];
					if (tx_clk_cnt == (CLKS_PER_BIT - 1)) begin
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
					if (tx_clk_cnt == (CLKS_PER_BIT - 1)) begin
						tx_state <= TX_IDLE;
					end else begin
						tx_clk_cnt <= tx_clk_cnt + 16'd1;
					end
				end
			endcase
		end
	end

	//status register: bit 0 = rx_ready (key available), bit 1 = tx_ready
	assign rdata = (addr == 4'h0) ? {24'd0, rx_data_reg} :
	               (addr == 4'h4) ? {30'd0, ~tx_busy, rx_ready} : 32'd0;

endmodule