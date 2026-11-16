import rv32_pkg::*;

module alu (
	input  alu_op_t alu_op,
	input  logic [31:0] A,
	input  logic [31:0] B,
	output logic [31:0] O
);
	logic lt_u;
	logic lt_s;
	assign lt_u = (A < B);
	assign lt_s = ($signed(A) < $signed(B));

	always_comb begin
		case (alu_op)
			// RV32I Base Arithmetic & Logic
			ALU_ADD:  O = A + B;
			ALU_SUB:  O = A - B;
			ALU_AND:  O = A & B;
			ALU_OR:   O = A | B;
			ALU_XOR:  O = A ^ B;
			ALU_SLTU: O = {31'b0, lt_u};
			ALU_SLT:  O = {31'b0, lt_s};
			ALU_SLL:  O = A << B[4:0];
			ALU_SRL:  O = A >> B[4:0];
			ALU_SRA:  O = $unsigned($signed(A) >>> B[4:0]);
			default:  O = 32'd0;
		endcase
	end

endmodule