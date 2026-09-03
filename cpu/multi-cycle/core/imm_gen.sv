import rv32_pkg::*;

module imm_gen (
	input  logic [31:0] instr,
	output logic [31:0] imm
);

	opcode_t opcode;
	assign opcode = opcode_t'(instr[6:0]);

	always_comb begin
		case (opcode)
			// I-type: Arithmetic with immediate, Loads, JALR
			OPC_OP_IMM, OPC_LOAD, OPC_JALR, OPC_SYSTEM: begin
				imm = { {20{instr[31]}}, instr[31:20] };
			end

			// S-type: Stores
			OPC_STORE: begin
				imm = { {20{instr[31]}}, instr[31:25], instr[11:7] };
			end

			// B-type: Conditional Branches
			OPC_BRANCH: begin
				imm = { {19{instr[31]}}, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0 };
			end

			// U-type: LUI, AUIPC
			OPC_LUI, OPC_AUIPC: begin
				imm = { instr[31:12], 12'b0 };
			end

			// J-type: JAL
			OPC_JAL: begin
				imm = { {11{instr[31]}}, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0 };
			end

			default: begin
				imm = 32'd0;
			end
		endcase
	end

endmodule