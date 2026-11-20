import rv32_pkg::*;

module datapath #(
	parameter logic [31:0] RESET_PC = 32'h0000_0000
)(
	input logic clk,
	input logic rst,

	input fsm_state_t fsm_state,

	//control lines
	input mem_addr_src_t mem_addr_src,
	input logic reg_we,
	input rf_wb_src_t rf_wb_src,
	input logic a_we,
	input logic b_we,
	input logic pc_we,
	input pc_src_t pc_src,
	input logic pc_4_we,
	input logic ir_we,
	input alu_src_a_t alu_src_a,
	input alu_src_b_t alu_src_b,
	input alu_op_t alu_op,
	input logic mul_en,
	input logic div_en,

	//mem interface
	output logic [31:0] mem_addr,
	output logic [31:0] mem_wdata,
	output logic [3:0] mem_wbe,
	input logic [31:0] mem_rdata,

	//to fsm
	output opcode_t opcode,
	output logic [2:0] funct3,
	output logic [6:0] funct7,
	output logic mul_done,
	output logic div_done
);
	//internal registers
	logic [31:0] pc;
	logic [31:0] pc_4;
	logic [31:0] ir;
	logic [31:0] reg_a;
	logic [31:0] reg_b;
	logic [1:0] load_byte_offset;

	//internal signals
	logic [4:0] rs1;
	logic [4:0] rs2;
	logic [4:0] rd;
	logic [31:0] imm;

	logic [31:0] rf_rdata1;
	logic [31:0] rf_rdata2;
	logic [31:0] rf_wdata;

	logic [31:0] alu_in_a;
	logic [31:0] alu_in_b;
	logic [31:0] alu_result;
	logic [31:0] mul_result;
	logic [31:0] div_result;

	logic [31:0] mem_parsed_rdata;
	logic [31:0] mem_unparsed_wdata;
	assign mem_unparsed_wdata = reg_b;

	assign mem_addr = (mem_addr_src == MEM_ADDR_PC) ? pc : alu_result;

	//instruction split
	logic [31:0] current_instr;
	assign current_instr = (fsm_state == STATE_DECODE) ? mem_rdata : ir;

	assign opcode = opcode_t'(current_instr[6:0]);
	assign funct3 = current_instr[14:12];
	assign funct7 = current_instr[31:25];
	assign rs1    = current_instr[19:15];
	assign rs2    = current_instr[24:20];
	assign rd     = current_instr[11:7];

	//branch handler
	logic branch_taken;
	always_comb begin
		case (funct3)
			FUNCT3_BEQ:  branch_taken = (reg_a == reg_b);
			FUNCT3_BNE:  branch_taken = (reg_a != reg_b);
			FUNCT3_BLT:  branch_taken = ($signed(reg_a) < $signed(reg_b));
			FUNCT3_BGE:  branch_taken = ($signed(reg_a) >= $signed(reg_b));
			FUNCT3_BLTU: branch_taken = (reg_a < reg_b);
			FUNCT3_BGEU: branch_taken = (reg_a >= reg_b);
			default:     branch_taken = 1'b0;
		endcase
	end

	//pc handler
	always_ff @(posedge clk) begin
		if (rst) begin
			pc <= RESET_PC;
		end else if (pc_we) begin
			case (pc_src)
				PC_SRC_PC4:     pc <= pc_4;
				PC_SRC_BRANCH:  pc <= (branch_taken ? alu_result : pc_4);
				PC_SRC_ALU:     pc <= alu_result & ~32'd1;
				default:        pc <= pc_4;
			endcase
		end
	end

	//staging registers
	always_ff @(posedge clk) begin
		if (rst) begin
			pc_4             <= 32'd0;
			ir               <= 32'h0000_0013;
			reg_a            <= 32'd0;
			reg_b            <= 32'd0;
			load_byte_offset <= 2'b00;
		end else begin
			if (pc_4_we)  pc_4  <= alu_result;
			if (ir_we)    ir    <= mem_rdata;
			if (a_we)     reg_a <= rf_rdata1;
			if (b_we)     reg_b <= rf_rdata2;
			if (fsm_state == STATE_LOAD_REQ) load_byte_offset <= alu_result[1:0];
		end
	end

	//load byte and halfword slicing wires
	logic [7:0]  loaded_byte;
	logic [15:0] loaded_half;

	always_comb begin
		case (load_byte_offset)
			2'b00:   loaded_byte = mem_rdata[7:0];
			2'b01:   loaded_byte = mem_rdata[15:8];
			2'b10:   loaded_byte = mem_rdata[23:16];
			2'b11:   loaded_byte = mem_rdata[31:24];
		endcase
	end

	assign loaded_half = load_byte_offset[1] ? mem_rdata[31:16] : mem_rdata[15:0];

	//mem handler
	always_comb begin
		mem_parsed_rdata = mem_rdata;
		mem_wdata        = mem_unparsed_wdata;
		mem_wbe          = 4'b0000;

		//loads
		case (funct3)
			FUNCT3_LB:  mem_parsed_rdata = {{24{loaded_byte[7]}}, loaded_byte};
			FUNCT3_LH:  mem_parsed_rdata = {{16{loaded_half[15]}}, loaded_half};
			FUNCT3_LW:  mem_parsed_rdata = mem_rdata;
			FUNCT3_LBU: mem_parsed_rdata = {24'b0, loaded_byte};
			FUNCT3_LHU: mem_parsed_rdata = {16'b0, loaded_half};
			default: ;
		endcase

		//stores (only active for store instructions)
		if (opcode == OPC_STORE) begin
			case (funct3)
				FUNCT3_SB: begin
					mem_wdata = {4{mem_unparsed_wdata[7:0]}};
					mem_wbe   = 4'b0001 << mem_addr[1:0];
				end
				FUNCT3_SH: begin
					mem_wdata = {2{mem_unparsed_wdata[15:0]}};
					mem_wbe   = mem_addr[1] ? 4'b1100 : 4'b0011;
				end
				FUNCT3_SW: begin
					mem_wdata = mem_unparsed_wdata;
					mem_wbe   = 4'b1111;
				end
				default: ;
			endcase
		end
	end

	//regfile writeback mux
	always_comb begin
		case (rf_wb_src)
			RF_WB_ALUOUT:  rf_wdata = alu_result;
			RF_WB_MUL:     rf_wdata = mul_result;
			RF_WB_DIV:     rf_wdata = div_result;
			RF_WB_MDR:     rf_wdata = mem_parsed_rdata;
			RF_WB_PC4:     rf_wdata = pc_4;
			RF_WB_IMM:     rf_wdata = imm;
			default:       rf_wdata = alu_result;
		endcase
	end

	//submodules
	imm_gen u_imm_gen (
		.instr (current_instr),
		.imm   (imm)
	);

	regfile u_regfile (
		.clk    (clk),
		.rs1    (rs1),
		.rs2    (rs2),
		.rd     (rd),
		.we     (reg_we),
		.dataIn (rf_wdata),
		.rs1O   (rf_rdata1),
		.rs2O   (rf_rdata2)
	);

	assign alu_in_a = (alu_src_a == ALU_SRC_A_REG) ? reg_a : pc;

	always_comb begin
		case (alu_src_b)
			ALU_SRC_B_REG: alu_in_b = reg_b;
			ALU_SRC_B_IMM: alu_in_b = imm;
			ALU_SRC_B_4:   alu_in_b = 4;
			default:       alu_in_b = reg_b;
		endcase
	end

	alu u_alu (
		.alu_op (alu_op),
		.A      (alu_in_a),
		.B      (alu_in_b),
		.O      (alu_result)
	);

	mul_unit u_mul_unit (
		.clk     (clk),
		.rst     (rst),
		.en      (mul_en),
		.funct3  (funct3),
		.rs1_val (reg_a),
		.rs2_val (reg_b),
		.done    (mul_done),
		.result  (mul_result)
	);

	div_unit u_div_unit (
		.clk     (clk),
		.rst     (rst),
		.en      (div_en),
		.funct3  (funct3),
		.rs1_val (reg_a),
		.rs2_val (reg_b),
		.done    (div_done),
		.result  (div_result)
	);

endmodule