import rv32_pkg::*;

module control_fsm (
    input logic clk,
    input logic rst,

    input opcode_t opcode,
    input logic [2:0] funct3,
    input logic [6:0] funct7,

    //live decode fields from mem_rdata (used strictly in STATE_DECODE next-state FF)
    input opcode_t dec_opcode,
    input logic [2:0] dec_funct3,
    input logic [6:0] dec_funct7,
    input logic [11:0] dec_funct12,
    input logic dec_rs1_zero,
    input logic dec_rd_zero,

    //trap condition flags from datapath
    input logic csr_illegal,
    input logic inst_misaligned,
    input logic load_misaligned,
    input logic store_misaligned,

    //outputs to BRAM
    output logic mem_we,
    output logic mem_req,
    output mem_addr_src_t mem_addr_src,

    //outputs to Register File
    output logic reg_we,
    output rf_wb_src_t rf_wb_src,
    
    output logic a_we,
    output logic b_we,

    //outputs to PC
    output logic pc_we,
    output pc_src_t pc_src,
    output logic pc_4_we,

    //output to ir
    output logic ir_we,

    //outputs to alu / mul / div
    output alu_src_a_t alu_src_a,
    output alu_src_b_t alu_src_b,
    output alu_op_t alu_op,
    input  logic mul_done,
    output logic mul_en,
    input  logic div_done,
    output logic div_en,

    //outputs to csr
    output logic csr_en,
    output logic trap_en,
    output logic mret_en,
    output logic [31:0] trap_cause,
    output trap_val_src_t trap_val_src,
    output logic instret_inc,

    output fsm_state_t fsm_state
);
    logic [31:0]   trap_cause_q;
    trap_val_src_t trap_val_src_q;

    always_ff @(posedge clk) begin
        if (rst) begin
            fsm_state      <= STATE_RESET;
            trap_cause_q   <= CAUSE_ECALL_M;
            trap_val_src_q <= TRAP_VAL_ZERO;
        end else begin
            case (fsm_state)
                STATE_RESET: fsm_state <= STATE_FETCH;

                STATE_FETCH: fsm_state <= STATE_DECODE;

                STATE_DECODE: begin
                    case (dec_opcode)
                        OPC_LUI, OPC_AUIPC, OPC_JAL: fsm_state <= STATE_IMM_PC;
                        OPC_BRANCH: begin
                            if (dec_funct3 inside {
                                FUNCT3_BEQ, FUNCT3_BNE, FUNCT3_BLT,
                                FUNCT3_BGE, FUNCT3_BLTU, FUNCT3_BGEU
                            }) begin
                                fsm_state <= STATE_IMM_PC;
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        OPC_OP: begin
                            if (dec_funct7 == FUNCT7_M_EXT) begin
                                if (dec_funct3 inside {FUNCT3_MUL, FUNCT3_MULH, FUNCT3_MULHSU, FUNCT3_MULHU}) begin
                                    fsm_state <= STATE_MUL;
                                end else begin
                                    fsm_state <= STATE_DIV;
                                end
                            end else if ((dec_funct7 == FUNCT7_BASE) ||
                                         ((dec_funct7 == FUNCT7_SUB) && (dec_funct3 inside {FUNCT3_ADD_SUB, FUNCT3_SRL_SRA}))) begin
                                fsm_state <= STATE_EXECUTE;
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        OPC_OP_IMM: begin
                            if (((dec_funct3 == FUNCT3_SLL)     && (dec_funct7 != FUNCT7_BASE)) ||
                                ((dec_funct3 == FUNCT3_SRL_SRA) && !(dec_funct7 inside {FUNCT7_BASE, FUNCT7_SRA}))) begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end else begin
                                fsm_state <= STATE_EXECUTE;
                            end
                        end
                        OPC_JALR: begin
                            if (dec_funct3 == FUNCT3_JALR) begin
                                fsm_state <= STATE_JALR;
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        OPC_STORE: begin
                            if (dec_funct3 inside {FUNCT3_SB, FUNCT3_SH, FUNCT3_SW}) begin
                                fsm_state <= STATE_STORE;
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        OPC_LOAD: begin
                            if (dec_funct3 inside {FUNCT3_LB, FUNCT3_LH, FUNCT3_LW, FUNCT3_LBU, FUNCT3_LHU}) begin
                                fsm_state <= STATE_LOAD_REQ;
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        OPC_FENCE: begin
                            if (dec_funct3 == FUNCT3_FENCE) begin
                                fsm_state <= STATE_IMM_PC;
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        OPC_SYSTEM: begin
                            if (dec_funct3 inside {
                                FUNCT3_CSRRW,  FUNCT3_CSRRS,  FUNCT3_CSRRC,
                                FUNCT3_CSRRWI, FUNCT3_CSRRSI, FUNCT3_CSRRCI
                            }) begin
                                fsm_state <= STATE_CSR;
                            end else if ((dec_funct3 == FUNCT3_PRIV) && dec_rs1_zero && dec_rd_zero) begin
                                if (dec_funct12 == FUNCT12_ECALL) begin
                                    fsm_state      <= STATE_TRAP;
                                    trap_cause_q   <= CAUSE_ECALL_M;
                                    trap_val_src_q <= TRAP_VAL_ZERO;
                                end else if (dec_funct12 == FUNCT12_EBREAK) begin
                                    fsm_state      <= STATE_TRAP;
                                    trap_cause_q   <= CAUSE_BREAKPOINT;
                                    trap_val_src_q <= TRAP_VAL_PC;
                                end else if (dec_funct12 == FUNCT12_MRET) begin
                                    fsm_state <= STATE_MRET;
                                end else begin
                                    fsm_state      <= STATE_TRAP;
                                    trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                    trap_val_src_q <= TRAP_VAL_IR;
                                end
                            end else begin
                                fsm_state      <= STATE_TRAP;
                                trap_cause_q   <= CAUSE_ILLEGAL_INST;
                                trap_val_src_q <= TRAP_VAL_IR;
                            end
                        end
                        default: begin
                            fsm_state      <= STATE_TRAP;
                            trap_cause_q   <= CAUSE_ILLEGAL_INST;
                            trap_val_src_q <= TRAP_VAL_IR;
                        end
                    endcase
                end

                STATE_IMM_PC: begin
                    if ((opcode inside {OPC_BRANCH, OPC_JAL}) && inst_misaligned) begin
                        fsm_state      <= STATE_TRAP;
                        trap_cause_q   <= CAUSE_INST_MISALIGNED;
                        trap_val_src_q <= TRAP_VAL_ADDR;
                    end else begin
                        fsm_state <= STATE_FETCH;
                    end
                end

                STATE_EXECUTE: fsm_state <= STATE_FETCH;

                STATE_MUL: fsm_state <= mul_done ? STATE_FETCH : STATE_MUL;

                STATE_DIV: fsm_state <= div_done ? STATE_FETCH : STATE_DIV;

                STATE_JALR: begin
                    if (inst_misaligned) begin
                        fsm_state      <= STATE_TRAP;
                        trap_cause_q   <= CAUSE_INST_MISALIGNED;
                        trap_val_src_q <= TRAP_VAL_ADDR;
                    end else begin
                        fsm_state <= STATE_FETCH;
                    end
                end

                STATE_STORE: begin
                    if (store_misaligned) begin
                        fsm_state      <= STATE_TRAP;
                        trap_cause_q   <= CAUSE_STORE_MISALIGNED;
                        trap_val_src_q <= TRAP_VAL_ADDR;
                    end else begin
                        fsm_state <= STATE_FETCH;
                    end
                end

                STATE_LOAD_REQ: begin
                    if (load_misaligned) begin
                        fsm_state      <= STATE_TRAP;
                        trap_cause_q   <= CAUSE_LOAD_MISALIGNED;
                        trap_val_src_q <= TRAP_VAL_ADDR;
                    end else begin
                        fsm_state <= STATE_LOAD_WB;
                    end
                end

                STATE_LOAD_WB: fsm_state <= STATE_FETCH;

                STATE_CSR: begin
                    if (csr_illegal) begin
                        fsm_state      <= STATE_TRAP;
                        trap_cause_q   <= CAUSE_ILLEGAL_INST;
                        trap_val_src_q <= TRAP_VAL_IR;
                    end else begin
                        fsm_state <= STATE_FETCH;
                    end
                end

                STATE_TRAP: fsm_state <= STATE_FETCH;

                STATE_MRET: fsm_state <= STATE_FETCH;

                default: fsm_state <= STATE_FETCH;
            endcase 
        end
    end
    
    always_comb begin
        mem_we       = 1'b0;
		mem_req      = 1'b0;
		mem_addr_src = MEM_ADDR_PC;
		reg_we       = 1'b0;
		rf_wb_src    = RF_WB_ALUOUT;
		a_we         = 1'b0;
		b_we         = 1'b0;
		pc_we        = 1'b0;
		pc_src       = PC_SRC_PC4;
        pc_4_we      = 1'b0;
		ir_we        = 1'b0;
        alu_src_a    = ALU_SRC_A_REG;
		alu_src_b    = ALU_SRC_B_REG;
		alu_op       = ALU_ADD;
		mul_en       = 1'b0;
		div_en       = 1'b0;
		csr_en       = 1'b0;
		trap_en      = 1'b0;
		mret_en      = 1'b0;
		trap_cause   = CAUSE_ECALL_M;
		trap_val_src = TRAP_VAL_ZERO;
		instret_inc  = 1'b0;

        case (fsm_state)
            STATE_RESET: begin
            end

            STATE_FETCH: begin
                mem_req = 1'b1;
                mem_addr_src = MEM_ADDR_PC;
            end

            STATE_DECODE: begin
                ir_we = 1'b1;
                a_we = 1'b1;
                b_we = 1'b1;
                alu_src_a = ALU_SRC_A_PC;
                alu_src_b = ALU_SRC_B_4;
                pc_4_we = 1'b1;
            end

            STATE_IMM_PC: begin
                alu_src_a = ALU_SRC_A_PC;
                alu_src_b = ALU_SRC_B_IMM;
                case (opcode)
                    OPC_BRANCH: begin
                        pc_we       = !inst_misaligned;
                        pc_src      = PC_SRC_BRANCH;
                        instret_inc = !inst_misaligned;
                    end
                    OPC_JAL: begin
                        reg_we      = !inst_misaligned;
                        rf_wb_src   = RF_WB_PC4;
                        pc_we       = !inst_misaligned;
                        pc_src      = PC_SRC_ALU;
                        instret_inc = !inst_misaligned;
                    end
                    OPC_LUI: begin
                        reg_we      = 1'b1;
                        rf_wb_src   = RF_WB_IMM;
                        pc_we       = 1'b1;
                        pc_src      = PC_SRC_PC4;
                        instret_inc = 1'b1;
                    end
                    OPC_AUIPC: begin
                        reg_we      = 1'b1;
                        rf_wb_src   = RF_WB_ALUOUT;
                        pc_we       = 1'b1;
                        pc_src      = PC_SRC_PC4;
                        instret_inc = 1'b1;
                    end
                    default: begin
                        pc_we       = 1'b1;
                        pc_src      = PC_SRC_PC4;
                        instret_inc = 1'b1;
                    end
                endcase
            end

            STATE_EXECUTE: begin
                reg_we = 1'b1;
                rf_wb_src = RF_WB_ALUOUT;
                pc_we = 1'b1;
                pc_src = PC_SRC_PC4;
                instret_inc = 1'b1;

                if (opcode == OPC_OP_IMM) begin
                    alu_src_b = ALU_SRC_B_IMM;
                end else begin
                    alu_src_b = ALU_SRC_B_REG;
                end

                case (funct3)
                    FUNCT3_ADD_SUB: begin
                        if ((opcode == OPC_OP) && (funct7 == FUNCT7_SUB)) begin
                            alu_op = ALU_SUB;
                        end else begin
                            alu_op = ALU_ADD;
                        end
                    end
                    FUNCT3_SLL: alu_op = ALU_SLL;
                    FUNCT3_SLT: alu_op = ALU_SLT;
                    FUNCT3_SLTU: alu_op = ALU_SLTU;
                    FUNCT3_XOR: alu_op = ALU_XOR;
                    FUNCT3_SRL_SRA: begin
                        if (funct7 == FUNCT7_SRA) begin
                            alu_op = ALU_SRA;
                        end else begin
                            alu_op = ALU_SRL;
                        end
                    end
                    FUNCT3_OR: alu_op = ALU_OR;
                    FUNCT3_AND: alu_op = ALU_AND;
                    default: ;
                endcase

            end

            STATE_MUL: begin
                mul_en = 1'b1;
                if (mul_done) begin
                    reg_we      = 1'b1;
                    rf_wb_src   = RF_WB_MUL;
                    pc_we       = 1'b1;
                    pc_src      = PC_SRC_PC4;
                    instret_inc = 1'b1;
                end
            end

            STATE_DIV: begin
                div_en = 1'b1;
                if (div_done) begin
                    reg_we      = 1'b1;
                    rf_wb_src   = RF_WB_DIV;
                    pc_we       = 1'b1;
                    pc_src      = PC_SRC_PC4;
                    instret_inc = 1'b1;
                end
            end

            STATE_JALR: begin
                alu_src_b   = ALU_SRC_B_IMM;
                alu_op      = ALU_ADD;
                pc_we       = !inst_misaligned;
                pc_src      = PC_SRC_ALU;
                reg_we      = !inst_misaligned;
                rf_wb_src   = RF_WB_PC4;
                instret_inc = !inst_misaligned;
            end

            STATE_STORE: begin
                alu_src_b    = ALU_SRC_B_IMM;
                alu_op       = ALU_ADD;
                mem_req      = !store_misaligned;
                mem_we       = !store_misaligned;
                mem_addr_src = MEM_ADDR_ALU;
                pc_we        = !store_misaligned;
                pc_src       = PC_SRC_PC4;
                instret_inc  = !store_misaligned;
            end

            STATE_LOAD_REQ: begin
                alu_src_b    = ALU_SRC_B_IMM;
                alu_op       = ALU_ADD;
                mem_req      = !load_misaligned;
                mem_addr_src = MEM_ADDR_ALU;
            end

            STATE_LOAD_WB: begin
                reg_we = 1'b1;
                rf_wb_src = RF_WB_MDR;
                pc_we = 1'b1;
                pc_src = PC_SRC_PC4;
                instret_inc = 1'b1;
            end

            STATE_CSR: begin
                csr_en      = 1'b1;
                reg_we      = !csr_illegal;
                rf_wb_src   = RF_WB_CSR;
                pc_we       = !csr_illegal;
                pc_src      = PC_SRC_PC4;
                instret_inc = !csr_illegal;
            end

            STATE_TRAP: begin
                trap_en      = 1'b1;
                pc_we        = 1'b1;
                pc_src       = PC_SRC_TRAP;
                trap_cause   = trap_cause_q;
                trap_val_src = trap_val_src_q;
            end

            STATE_MRET: begin
                mret_en     = 1'b1;
                pc_we       = 1'b1;
                pc_src      = PC_SRC_MEPC;
                instret_inc = 1'b1;
            end

            default: ;
        endcase
    end
    
endmodule