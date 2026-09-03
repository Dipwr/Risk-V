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

	localparam logic [6:0] FUNCT7_BASE     = 7'b0000000; 
	localparam logic [6:0] FUNCT7_SUB      = 7'b0100000;
    localparam logic [6:0] FUNCT7_SRA      = 7'b0100000;
	localparam logic [6:0] FUNCT7_M_EXT    = 7'b0000001; 

	typedef enum logic [4:0] {
		ALU_ADD,
		ALU_SUB,
		ALU_AND,
		ALU_OR,
		ALU_XOR,
		ALU_SLT,
		ALU_SLTU,
		ALU_SLL,
		ALU_SRL,
		ALU_SRA,
		ALU_MUL,
		ALU_MULH,
		ALU_MULHU,
		ALU_MULHSU,
		ALU_DIV,
		ALU_DIVU,
		ALU_REM,
		ALU_REMU
	} alu_op_t;

	// Source for next Program Counter
	typedef enum logic [1:0] {
		PC_SRC_PC4, 
		PC_SRC_BRANCH,
		PC_SRC_ALU,
		PC_SRC_ADADDER
	} pc_src_t;

	// Sources for ALU input B
	typedef enum logic {
		ALU_SRC_B_REG,    
		ALU_SRC_B_IMM  
	} alu_src_b_t;

	// Source for Register File writeback data
	typedef enum logic [2:0] {
		RF_WB_ALUOUT,   
		RF_WB_MDR,      
		RF_WB_PC4,
		RF_WB_IMM,
		RF_WB_ADADDER
	} rf_wb_src_t;

	// Address multiplexer to BRAM
	typedef enum logic {
		MEM_ADDR_PC,
		MEM_ADDR_ALU
	} mem_addr_src_t;

endpackage