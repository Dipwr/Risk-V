import rv32_pkg::*;

module control_fsm (
    input logic clk,
    input logic rst,

    input opcode_t opcode,
    input logic [2:0] funct3,
    input logic [6:0] funct7,

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

    //output to ir
    output logic ir_we,

    //outputs to alu
    output alu_src_b_t alu_src_b,
    output alu_op_t alu_op,

    output fsm_state_t fsm_state
);
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            fsm_state <= STATE_RESET;
        end else begin
            case (fsm_state)
                STATE_RESET: fsm_state <= STATE_FETCH;

                STATE_FETCH: fsm_state <= STATE_DECODE;

                STATE_DECODE: begin
                    case (opcode)
                        OPC_BRANCH, OPC_JAL, OPC_LUI, OPC_AUIPC: fsm_state <= STATE_FETCH;
                        OPC_OP, OPC_OP_IMM: fsm_state <= STATE_EXECUTE;
                        OPC_JALR: fsm_state <= STATE_JALR;
                        OPC_STORE: fsm_state <= STATE_STORE;
                        OPC_LOAD: fsm_state <= STATE_LOAD_REQ;
                        default: fsm_state <= STATE_FETCH;
                    endcase
                end

                STATE_EXECUTE: fsm_state <= STATE_FETCH;

                STATE_JALR: fsm_state <= STATE_FETCH;

                STATE_STORE: fsm_state <= STATE_FETCH;

                STATE_LOAD_REQ: fsm_state <= STATE_LOAD_WB;

                STATE_LOAD_WB: fsm_state <= STATE_FETCH;

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
		ir_we        = 1'b0;
		alu_src_b    = ALU_SRC_B_REG;
		alu_op       = ALU_ADD;

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

                case (opcode)
                    OPC_BRANCH:begin
                        pc_we = 1'b1;
                        pc_src = PC_SRC_BRANCH;
                    end
                    OPC_JAL:begin
                        reg_we = 1'b1;
                        rf_wb_src = RF_WB_PC4;
                        pc_we = 1'b1;
                        pc_src = PC_SRC_ADADDER;
                    end
                    OPC_LUI: begin
                        reg_we = 1'b1;
                        rf_wb_src = RF_WB_IMM;
                        pc_we = 1'b1;
                        pc_src = PC_SRC_PC4;
                    end
                    OPC_AUIPC: begin
                        reg_we = 1'b1;
                        rf_wb_src = RF_WB_ADADDER;
                        pc_we = 1'b1;
                        pc_src = PC_SRC_PC4;
                    end
                    default: ;
                endcase
            end

            STATE_EXECUTE: begin
                reg_we = 1'b1;
                rf_wb_src = RF_WB_ALUOUT;
                pc_we = 1'b1;
                pc_src = PC_SRC_PC4;

                if (opcode == OPC_OP_IMM) begin
                    alu_src_b = ALU_SRC_B_IMM;
                end else begin
                    alu_src_b = ALU_SRC_B_REG;
                end

                if ((opcode == OPC_OP) && (funct7 == FUNCT7_M_EXT))begin
                    case (funct3)
                        FUNCT3_MUL: alu_op = ALU_MUL;
                        FUNCT3_MULH: alu_op = ALU_MULH;
                        FUNCT3_MULHSU: alu_op = ALU_MULHSU;
                        FUNCT3_MULHU: alu_op = ALU_MULHU;
                        FUNCT3_DIV: alu_op = ALU_DIV;
                        FUNCT3_DIVU: alu_op = ALU_DIVU;
                        FUNCT3_REM: alu_op = ALU_REM;
                        FUNCT3_REMU: alu_op = ALU_REMU;
                        default: ;
                    endcase
                end else begin
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

            end

            STATE_JALR: begin
                alu_src_b = ALU_SRC_B_IMM;
                alu_op = ALU_ADD;
                pc_we = 1'b1;
                pc_src = PC_SRC_ALU;
                reg_we = 1'b1;
                rf_wb_src = RF_WB_PC4;
            end

            STATE_STORE: begin
                alu_src_b = ALU_SRC_B_IMM;
                alu_op = ALU_ADD;
                mem_req = 1'b1;
                mem_we = 1'b1;
                mem_addr_src = MEM_ADDR_ALU;
                pc_we = 1'b1;
                pc_src = PC_SRC_PC4;
            end

            STATE_LOAD_REQ: begin
                alu_src_b = ALU_SRC_B_IMM;
                alu_op = ALU_ADD;
                mem_req = 1'b1;
                mem_addr_src = MEM_ADDR_ALU;
            end

            STATE_LOAD_WB: begin
                reg_we = 1'b1;
                rf_wb_src = RF_WB_MDR;
                pc_we = 1'b1;
                pc_src = PC_SRC_PC4;
            end

            default: ;
        endcase
    end
    
endmodule