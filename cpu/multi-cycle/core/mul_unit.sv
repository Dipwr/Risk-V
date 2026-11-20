import rv32_pkg::*;

module mul_unit (
	input  logic        clk,
	input  logic        rst,
	input  logic        en,
	input  logic [2:0]  funct3,
	input  logic [31:0] rs1_val,
	input  logic [31:0] rs2_val,
	output logic        done,
	output logic [31:0] result
);
	// Sign/zero extension based on RV32M multiply variant
	logic signed [32:0] a_ext;
	logic signed [32:0] b_ext;

	always_comb begin
		case (funct3)
			FUNCT3_MULHU: begin
				a_ext = $signed({1'b0, rs1_val});
				b_ext = $signed({1'b0, rs2_val});
			end
			FUNCT3_MULHSU: begin
				a_ext = $signed({rs1_val[31], rs1_val});
				b_ext = $signed({1'b0, rs2_val});
			end
			default: begin // FUNCT3_MUL, FUNCT3_MULH
				a_ext = $signed({rs1_val[31], rs1_val});
				b_ext = $signed({rs2_val[31], rs2_val});
			end
		endcase
	end

	// 2-stage DSP48E1 pipeline (MREG -> PREG); inputs come directly from reg_a/reg_b FFs.
	// No reset on pipeline regs so Vivado can pack them into DSP48E1 slices.
	logic signed [65:0] s1_prod;
	logic signed [65:0] s2_prod;

	always_ff @(posedge clk) begin
		s1_prod <= a_ext * b_ext;
		s2_prod <= s1_prod;
	end

	// 2 pipeline cycles + 1 writeback cycle
	logic [1:0] cycle_cnt;

	always_ff @(posedge clk) begin
		if (rst) begin
			cycle_cnt <= 2'd0;
		end else if (!en || (cycle_cnt == 2'd2)) begin
			cycle_cnt <= 2'd0;
		end else begin
			cycle_cnt <= cycle_cnt + 2'd1;
		end
	end

	assign done   = en && (cycle_cnt == 2'd2);
	assign result = (funct3 == FUNCT3_MUL) ? s2_prod[31:0] : s2_prod[63:32];

endmodule
