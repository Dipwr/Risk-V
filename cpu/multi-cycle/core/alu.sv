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

	logic signed [32:0] mul_a;
	logic signed [32:0] mul_b;
	logic signed [65:0] mul_prod;

	always_comb begin
		// Determine sign extension for operand A
		case (alu_op)
			ALU_MULHU: mul_a = {1'b0, A};       // Unsigned
			default:   mul_a = {A[31], A};      // Signed (MUL, MULH, MULHSU)
		endcase

		// Determine sign extension for operand B
		case (alu_op)
			ALU_MULHU,
			ALU_MULHSU: mul_b = {1'b0, B};      // Unsigned
			default:    mul_b = {B[31], B};     // Signed (MUL, MULH)
		endcase
	end

	assign mul_prod = mul_a * mul_b;

	logic div_by_zero;
	logic div_overflow;
	assign div_by_zero  = (B == 32'd0);
	assign div_overflow = (A == 32'h8000_0000) && (B == 32'hFFFF_FFFF);

	always_comb begin
		case (alu_op)
			// RV32I Base Arithmetic & Logic
			ALU_ADD:    O = A + B;
			ALU_SUB:    O = A - B;
			ALU_AND:    O = A & B;
			ALU_OR:     O = A | B;
			ALU_XOR:    O = A ^ B;
			ALU_SLTU:   O = {31'b0, lt_u};
			ALU_SLT:    O = {31'b0, lt_s};
			ALU_SLL:    O = A << B[4:0];
			ALU_SRL:    O = A >> B[4:0];
			ALU_SRA:    O = $unsigned($signed(A) >>> B[4:0]);

			// RV32M Multiply Operations
			ALU_MUL:    O = mul_prod[31:0];
			ALU_MULH,
			ALU_MULHU,
			ALU_MULHSU: O = mul_prod[63:32];

			// RV32M Division & Remainder Operations
			/*ALU_DIV: begin
				if (div_by_zero)       O = 32'hFFFF_FFFF;
				else if (div_overflow) O = 32'h8000_0000;
				else                   O = $unsigned($signed(A) / $signed(B));
			end

			ALU_DIVU: begin
				if (div_by_zero)       O = 32'hFFFF_FFFF;
				else                   O = A / B;
			end

			ALU_REM: begin
				if (div_by_zero)       O = A;
				else if (div_overflow) O = 32'd0;
				else                   O = $unsigned($signed(A) % $signed(B));
			end

			ALU_REMU: begin
				if (div_by_zero)       O = A;
				else                   O = A % B;
			end*/

			ALU_DIV,
			ALU_DIVU,
			ALU_REM,
			ALU_REMU: begin
				O = 32'd0;
			end

			default: O = 32'd0;
		endcase
	end

endmodule