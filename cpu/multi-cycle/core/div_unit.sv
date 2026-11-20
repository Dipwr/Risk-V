import rv32_pkg::*;

module div_unit (
	input  logic        clk,
	input  logic        rst,
	input  logic        en,
	input  logic [2:0]  funct3,
	input  logic [31:0] rs1_val,
	input  logic [31:0] rs2_val,
	output logic        done,
	output logic [31:0] result
);
	typedef enum logic [1:0] {
		DIV_IDLE,
		DIV_RUN,
		DIV_DONE
	} div_state_t;

	div_state_t div_state;
	logic [4:0]  bit_cnt;
	logic [31:0] quot_reg;
	logic [31:0] rem_reg;
	logic [31:0] divisor_reg;
	logic        q_neg_reg;
	logic        r_neg_reg;

	logic is_signed;
	logic is_rem;
	assign is_signed = (funct3 == FUNCT3_DIV) || (funct3 == FUNCT3_REM);
	assign is_rem    = (funct3 == FUNCT3_REM) || (funct3 == FUNCT3_REMU);

	logic div_by_zero;
	logic div_overflow;
	assign div_by_zero  = (rs2_val == 32'd0);
	assign div_overflow = is_signed && (rs1_val == 32'h8000_0000) && (rs2_val == 32'hFFFF_FFFF);

	// 33-bit trial remainder {rem_reg, quot_reg[31]} minus 32-bit divisor
	logic [32:0] shifted_rem;
	logic [33:0] sub_res;
	assign shifted_rem = {rem_reg, quot_reg[31]};
	assign sub_res     = {1'b0, shifted_rem} - {2'b00, divisor_reg};

	always_ff @(posedge clk) begin
		if (rst) begin
			div_state   <= DIV_IDLE;
			bit_cnt     <= 5'd0;
			quot_reg    <= 32'd0;
			rem_reg     <= 32'd0;
			divisor_reg <= 32'd0;
			q_neg_reg   <= 1'b0;
			r_neg_reg   <= 1'b0;
		end else if (!en) begin
			div_state <= DIV_IDLE;
			bit_cnt   <= 5'd0;
		end else begin
			case (div_state)
				DIV_IDLE: begin
					bit_cnt <= 5'd0;
					if (div_by_zero) begin
						quot_reg  <= 32'hFFFF_FFFF;
						rem_reg   <= rs1_val;
						q_neg_reg <= 1'b0;
						r_neg_reg <= 1'b0;
						div_state <= DIV_DONE;
					end else if (div_overflow) begin
						quot_reg  <= 32'h8000_0000;
						rem_reg   <= 32'd0;
						q_neg_reg <= 1'b0;
						r_neg_reg <= 1'b0;
						div_state <= DIV_DONE;
					end else begin
						quot_reg    <= (is_signed && rs1_val[31]) ? (~rs1_val + 32'd1) : rs1_val;
						divisor_reg <= (is_signed && rs2_val[31]) ? (~rs2_val + 32'd1) : rs2_val;
						rem_reg     <= 32'd0;
						q_neg_reg   <= is_signed && (rs1_val[31] ^ rs2_val[31]);
						r_neg_reg   <= is_signed && rs1_val[31];
						div_state   <= DIV_RUN;
					end
				end

				DIV_RUN: begin
					if (!sub_res[33]) begin
						rem_reg  <= sub_res[31:0];
						quot_reg <= {quot_reg[30:0], 1'b1};
					end else begin
						rem_reg  <= shifted_rem[31:0];
						quot_reg <= {quot_reg[30:0], 1'b0};
					end

					if (bit_cnt == 5'd31) begin
						div_state <= DIV_DONE;
					end else begin
						bit_cnt <= bit_cnt + 5'd1;
					end
				end

				DIV_DONE: begin
					div_state <= DIV_IDLE;
				end

				default: div_state <= DIV_IDLE;
			endcase
		end
	end

	// Mux unsigned result and sign flag before a single shared 32-bit negator
	logic [31:0] raw_res;
	logic        neg_res;
	assign raw_res = is_rem ? rem_reg : quot_reg;
	assign neg_res = is_rem ? r_neg_reg : q_neg_reg;

	assign done   = en && (div_state == DIV_DONE);
	assign result = neg_res ? (~raw_res + 32'd1) : raw_res;

endmodule
