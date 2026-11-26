package rv32_pkg;
	typedef enum logic [6:0] {
		OPC_LUI      = 7'b0110111,
		OPC_AUIPC    = 7'b0010111,
		OPC_JAL      = 7'b1101111,
		OPC_JALR     = 7'b1100111,
		OPC_BRANCH   = 7'b1100011,
		OPC_LOAD     = 7'b0000011,
		OPC_STORE    = 7'b0100011,
		OPC_OP_IMM   = 7'b0010011,
		OPC_OP       = 7'b0110011,
		OPC_SYSTEM   = 7'b1110011,
		OPC_FENCE    = 7'b0001111
	} opcode_t;

	// Branch conditions (OPC_BRANCH)
	localparam logic [2:0] FUNCT3_JALR     = 3'b000;
	localparam logic [2:0] FUNCT3_FENCE    = 3'b000;
	localparam logic [2:0] FUNCT3_BEQ      = 3'b000;
	localparam logic [2:0] FUNCT3_BNE      = 3'b001;
	localparam logic [2:0] FUNCT3_BLT      = 3'b100;
	localparam logic [2:0] FUNCT3_BGE      = 3'b101;
	localparam logic [2:0] FUNCT3_BLTU     = 3'b110;
	localparam logic [2:0] FUNCT3_BGEU     = 3'b111;

	// Load operations (OPC_LOAD)
	localparam logic [2:0] FUNCT3_LB       = 3'b000;
	localparam logic [2:0] FUNCT3_LH       = 3'b001;
	localparam logic [2:0] FUNCT3_LW       = 3'b010;
	localparam logic [2:0] FUNCT3_LBU      = 3'b100;
	localparam logic [2:0] FUNCT3_LHU      = 3'b101;

	// Store operations (OPC_STORE)
	localparam logic [2:0] FUNCT3_SB       = 3'b000;
	localparam logic [2:0] FUNCT3_SH       = 3'b001;
	localparam logic [2:0] FUNCT3_SW       = 3'b010;

	// Integer Arithmetic/Logic (OPC_OP and OPC_OP_IMM)
	localparam logic [2:0] FUNCT3_ADD_SUB  = 3'b000; // ADD, SUB, ADDI
	localparam logic [2:0] FUNCT3_SLL      = 3'b001; // SLL, SLLI
	localparam logic [2:0] FUNCT3_SLT      = 3'b010; // SLT, SLTI
	localparam logic [2:0] FUNCT3_SLTU     = 3'b011; // SLTU, SLTIU
	localparam logic [2:0] FUNCT3_XOR      = 3'b100; // XOR, XORI
	localparam logic [2:0] FUNCT3_SRL_SRA  = 3'b101; // SRL, SRA, SRLI, SRAI
	localparam logic [2:0] FUNCT3_OR       = 3'b110; // OR, ORI
	localparam logic [2:0] FUNCT3_AND      = 3'b111; // AND, ANDI

	// RV32M Multiply/Divide
	localparam logic [2:0] FUNCT3_MUL      = 3'b000;
	localparam logic [2:0] FUNCT3_MULH     = 3'b001;
	localparam logic [2:0] FUNCT3_MULHSU   = 3'b010;
	localparam logic [2:0] FUNCT3_MULHU    = 3'b011;
	localparam logic [2:0] FUNCT3_DIV      = 3'b100;
	localparam logic [2:0] FUNCT3_DIVU     = 3'b101;
	localparam logic [2:0] FUNCT3_REM      = 3'b110;
	localparam logic [2:0] FUNCT3_REMU     = 3'b111;

	// Zicsr Extension (OPC_SYSTEM)
	localparam logic [2:0] FUNCT3_PRIV     = 3'b000; // ECALL, EBREAK, MRET
	localparam logic [2:0] FUNCT3_CSRRW    = 3'b001;
	localparam logic [2:0] FUNCT3_CSRRS    = 3'b010;
	localparam logic [2:0] FUNCT3_CSRRC    = 3'b011;
	localparam logic [2:0] FUNCT3_CSRRWI   = 3'b101;
	localparam logic [2:0] FUNCT3_CSRRSI   = 3'b110;
	localparam logic [2:0] FUNCT3_CSRRCI   = 3'b111;

	// Privileged funct12 encodings (OPC_SYSTEM, FUNCT3_PRIV)
	localparam logic [11:0] FUNCT12_ECALL  = 12'h000;
	localparam logic [11:0] FUNCT12_EBREAK = 12'h001;
	localparam logic [11:0] FUNCT12_MRET   = 12'h302;

	localparam logic [6:0] FUNCT7_BASE     = 7'b0000000; 
	localparam logic [6:0] FUNCT7_SUB      = 7'b0100000;
    localparam logic [6:0] FUNCT7_SRA      = 7'b0100000;
	localparam logic [6:0] FUNCT7_M_EXT    = 7'b0000001;

	//CSRs
	localparam logic [1:0]  CSR_RO_PREFIX = 2'b11;

	// Unprivileged read-only counters (Zicntr)
	localparam logic [11:0] CSR_CYCLE     = 12'hC00;
	localparam logic [11:0] CSR_TIME      = 12'hC01;
	localparam logic [11:0] CSR_INSTRET   = 12'hC02;
	localparam logic [11:0] CSR_CYCLEH    = 12'hC80;
	localparam logic [11:0] CSR_TIMEH     = 12'hC81;
	localparam logic [11:0] CSR_INSTRETH  = 12'hC82;

	// Machine counters (writable aliases of cycle/instret)
	localparam logic [11:0] CSR_MCYCLE    = 12'hB00;
	localparam logic [11:0] CSR_MINSTRET  = 12'hB02;
	localparam logic [11:0] CSR_MCYCLEH   = 12'hB80;
	localparam logic [11:0] CSR_MINSTRETH = 12'hB82;

	// Machine information & trap setup/handling CSRs
	localparam logic [11:0] CSR_MSTATUS   = 12'h300;
	localparam logic [11:0] CSR_MISA      = 12'h301;
	localparam logic [11:0] CSR_MIE       = 12'h304;
	localparam logic [11:0] CSR_MTVEC     = 12'h305;
	localparam logic [11:0] CSR_MSCRATCH  = 12'h340;
	localparam logic [11:0] CSR_MEPC      = 12'h341;
	localparam logic [11:0] CSR_MCAUSE    = 12'h342;
	localparam logic [11:0] CSR_MTVAL     = 12'h343;
	localparam logic [11:0] CSR_MIP       = 12'h344;
	localparam logic [11:0] CSR_MVENDORID = 12'hF11;
	localparam logic [11:0] CSR_MARCHID   = 12'hF12;
	localparam logic [11:0] CSR_MIMPID    = 12'hF13;
	localparam logic [11:0] CSR_MHARTID   = 12'hF14;

	// RV32IM misa value: MXL=1 (32-bit, bits [31:30]), I (bit 8), M (bit 12)
	localparam logic [31:0] MISA_RV32IM   = 32'h4000_1100;

	// Machine exception cause codes (mcause[31] == 0)
	localparam logic [31:0] CAUSE_INST_MISALIGNED  = 32'd0;
	localparam logic [31:0] CAUSE_ILLEGAL_INST     = 32'd2;
	localparam logic [31:0] CAUSE_BREAKPOINT       = 32'd3;
	localparam logic [31:0] CAUSE_LOAD_MISALIGNED  = 32'd4;
	localparam logic [31:0] CAUSE_STORE_MISALIGNED = 32'd6;
	localparam logic [31:0] CAUSE_ECALL_M          = 32'd11;

	// Machine interrupt cause codes (mcause[31] == 1)
	localparam logic [31:0] CAUSE_IRQ_M_TIMER      = 32'h8000_0007;
	localparam logic [31:0] CAUSE_IRQ_M_EXT        = 32'h8000_000B;

	typedef enum logic [3:0] {
		ALU_ADD,
		ALU_SUB,
		ALU_AND,
		ALU_OR,
		ALU_XOR,
		ALU_SLT,
		ALU_SLTU,
		ALU_SLL,
		ALU_SRL,
		ALU_SRA
	} alu_op_t;

	// Source for next Program Counter
	typedef enum logic [2:0] {
		PC_SRC_PC4, 
		PC_SRC_BRANCH,
		PC_SRC_ALU,
		PC_SRC_TRAP,
		PC_SRC_MEPC
	} pc_src_t;

	// Source for mtval on trap entry
	typedef enum logic [1:0] {
		TRAP_VAL_ZERO,
		TRAP_VAL_PC,
		TRAP_VAL_IR,
		TRAP_VAL_ADDR
	} trap_val_src_t;

	// Sources for ALU input A
	typedef enum logic {
		ALU_SRC_A_REG,    
		ALU_SRC_A_PC
	} alu_src_a_t;

	// Sources for ALU input B
	typedef enum logic [1:0] {
		ALU_SRC_B_REG,    
		ALU_SRC_B_IMM,
		ALU_SRC_B_4
	} alu_src_b_t;

	// Source for Register File writeback data
	typedef enum logic [2:0] {
		RF_WB_ALUOUT,
		RF_WB_MUL,
		RF_WB_DIV,   
		RF_WB_MDR,      
		RF_WB_PC4,
		RF_WB_IMM,
		RF_WB_CSR
	} rf_wb_src_t;

	// Address multiplexer to BRAM
	typedef enum logic {
		MEM_ADDR_PC,
		MEM_ADDR_ALU
	} mem_addr_src_t;

	typedef enum logic [3:0] {
		STATE_RESET,
		STATE_FETCH,
		STATE_DECODE,
		STATE_IMM_PC,
		STATE_EXECUTE,
		STATE_MUL,
		STATE_DIV,
		STATE_JALR,
		STATE_STORE,
		STATE_LOAD_REQ,
		STATE_LOAD_WB,
		STATE_CSR,
		STATE_TRAP,
		STATE_MRET
	} fsm_state_t;

endpackage