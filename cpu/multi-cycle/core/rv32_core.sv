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
	logic          ir_we;
	alu_src_b_t    alu_src_b;
	alu_op_t       alu_op;
	fsm_state_t    fsm_state;

	//internal fsm memory controls
	logic          fsm_mem_req;
	logic          fsm_mem_we;

	//internal datapath to fsm signals
	opcode_t       opcode;
	logic [2:0]    funct3;
	logic [6:0]    funct7;

	//internal datapath byte enable
	logic [3:0]    dp_mem_wbe;

	//external memory output assignments
	assign mem_req   = fsm_mem_req;
	assign mem_wstrb = (fsm_mem_req && fsm_mem_we) ? dp_mem_wbe : 4'b0000;

	//fsm instance
	control_fsm u_control_fsm (
		.clk          (clk),
		.rst          (rst),
		.opcode       (opcode),
		.funct3       (funct3),
		.funct7       (funct7),
		.mem_we       (fsm_mem_we),
		.mem_req      (fsm_mem_req),
		.mem_addr_src (mem_addr_src),
		.reg_we       (reg_we),
		.rf_wb_src    (rf_wb_src),
		.a_we         (a_we),
		.b_we         (b_we),
		.pc_we        (pc_we),
		.pc_src       (pc_src),
		.ir_we        (ir_we),
		.alu_src_b    (alu_src_b),
		.alu_op       (alu_op),
        .fsm_state    (fsm_state)
	);

	//datapath instance
	datapath u_datapath (
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
		.ir_we        (ir_we),
		.alu_src_b    (alu_src_b),
		.alu_op       (alu_op),
		.mem_addr     (mem_addr),
		.mem_wdata    (mem_wdata),
		.mem_wbe      (dp_mem_wbe),
		.mem_rdata    (mem_rdata),
		.opcode       (opcode),
		.funct3       (funct3),
		.funct7       (funct7)
	);

endmodule