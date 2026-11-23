import rv32_pkg::*;

module rv32_core #(
	parameter logic [31:0] RESET_PC = 32'h0000_0000
)(
	input logic clk,
	input logic rst,

	//unified memory bus
	output logic        mem_req,
	output logic [3:0]  mem_wstrb,
	output logic [31:0] mem_addr,
	output logic [31:0] mem_wdata,
	input  logic [31:0] mem_rdata
);
	//internal fsm to datapath controls
	mem_addr_src_t mem_addr_src;
	logic          reg_we;
	rf_wb_src_t    rf_wb_src;
	logic          a_we;
	logic          b_we;
	logic          pc_we;
	pc_src_t       pc_src;
	logic          pc_4_we;
	logic          ir_we;
	alu_src_a_t    alu_src_a;
	alu_src_b_t    alu_src_b;
	alu_op_t       alu_op;
	logic          mul_en;
	logic          div_en;
	logic          csr_en;
	logic          trap_en;
	logic          mret_en;
	logic [31:0]   trap_cause;
	trap_val_src_t trap_val_src;
	logic          instret_inc;
	fsm_state_t    fsm_state;

	//internal fsm memory controls
	logic          fsm_mem_req;
	logic          fsm_mem_we;

	//internal datapath to fsm signals
	opcode_t       opcode;
	logic [2:0]    funct3;
	logic [6:0]    funct7;
	opcode_t       dec_opcode;
	logic [2:0]    dec_funct3;
	logic [6:0]    dec_funct7;
	logic [11:0]   dec_funct12;
	logic          dec_rs1_zero;
	logic          dec_rd_zero;
	logic          csr_illegal;
	logic          inst_misaligned;
	logic          load_misaligned;
	logic          store_misaligned;
	logic          mul_done;
	logic          div_done;

	//internal datapath byte enable
	logic [3:0]    dp_mem_wbe;

	//external memory output assignments
	assign mem_req   = fsm_mem_req;
	assign mem_wstrb = (fsm_mem_req && fsm_mem_we) ? dp_mem_wbe : 4'b0000;

	//fsm instance
	control_fsm u_control_fsm (
		.clk          (clk),
		.rst          (rst),
		.opcode           (opcode),
		.funct3           (funct3),
		.funct7           (funct7),
		.dec_opcode       (dec_opcode),
		.dec_funct3       (dec_funct3),
		.dec_funct7       (dec_funct7),
		.dec_funct12      (dec_funct12),
		.dec_rs1_zero     (dec_rs1_zero),
		.dec_rd_zero      (dec_rd_zero),
		.csr_illegal      (csr_illegal),
		.inst_misaligned  (inst_misaligned),
		.load_misaligned  (load_misaligned),
		.store_misaligned (store_misaligned),
		.mem_we       (fsm_mem_we),
		.mem_req      (fsm_mem_req),
		.mem_addr_src (mem_addr_src),
		.reg_we       (reg_we),
		.rf_wb_src    (rf_wb_src),
		.a_we         (a_we),
		.b_we         (b_we),
		.pc_we        (pc_we),
		.pc_src       (pc_src),
		.pc_4_we      (pc_4_we),
		.ir_we        (ir_we),
		.alu_src_a    (alu_src_a),
		.alu_src_b    (alu_src_b),
		.alu_op       (alu_op),
		.mul_done     (mul_done),
		.mul_en       (mul_en),
		.div_done     (div_done),
		.div_en       (div_en),
		.csr_en       (csr_en),
		.trap_en      (trap_en),
		.mret_en      (mret_en),
		.trap_cause   (trap_cause),
		.trap_val_src (trap_val_src),
		.instret_inc  (instret_inc),
        .fsm_state    (fsm_state)
	);

	//datapath instance
	datapath #(
		.RESET_PC (RESET_PC)
	) u_datapath (
		.clk          (clk),
		.rst          (rst),
		.fsm_state    (fsm_state),
		.mem_addr_src (mem_addr_src),
		.reg_we       (reg_we),
		.rf_wb_src    (rf_wb_src),
		.a_we         (a_we),
		.b_we         (b_we),
		.pc_we        (pc_we),
		.pc_src       (pc_src),
		.pc_4_we      (pc_4_we),
		.ir_we        (ir_we),
		.alu_src_a    (alu_src_a),
		.alu_src_b    (alu_src_b),
		.alu_op       (alu_op),
		.mul_en       (mul_en),
		.div_en       (div_en),
		.csr_en       (csr_en),
		.trap_en      (trap_en),
		.mret_en      (mret_en),
		.trap_cause   (trap_cause),
		.trap_val_src (trap_val_src),
		.instret_inc  (instret_inc),
		.mem_addr     (mem_addr),
		.mem_wdata    (mem_wdata),
		.mem_wbe      (dp_mem_wbe),
		.mem_rdata    (mem_rdata),
		.opcode           (opcode),
		.funct3           (funct3),
		.funct7           (funct7),
		.dec_opcode       (dec_opcode),
		.dec_funct3       (dec_funct3),
		.dec_funct7       (dec_funct7),
		.dec_funct12      (dec_funct12),
		.dec_rs1_zero     (dec_rs1_zero),
		.dec_rd_zero      (dec_rd_zero),
		.csr_illegal      (csr_illegal),
		.inst_misaligned  (inst_misaligned),
		.load_misaligned  (load_misaligned),
		.store_misaligned (store_misaligned),
		.mul_done     (mul_done),
		.div_done     (div_done)
	);

endmodule