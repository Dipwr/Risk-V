import rv32_pkg::*;

module csr_unit (
    input  logic        clk,
    input  logic        rst,
    
    input  logic        en,
    input  logic        instret_inc,
    
    input  logic [11:0] csr_addr,
    input  logic [2:0]  funct3,
    input  logic [4:0]  uimm,
    input  logic        rd_zero,
    
    input  logic [31:0] rs1_val, 

    // Hardware trap & MRET interface
    input  logic        trap_en,
    input  logic        mret_en,
    input  logic [31:2] trap_pc_base,
    input  logic [31:0] trap_cause,
    input  logic [31:0] trap_val,

    output logic [31:0] rdata,
    output logic [31:0] mtvec_out,
    output logic [31:0] mepc_out,
    output logic        illegal_csr
);
    logic [31:0] source;

    logic do_read;
    logic do_write;

    assign source = (funct3 inside {FUNCT3_CSRRW, FUNCT3_CSRRS, FUNCT3_CSRRC}) ? rs1_val : {27'b0, uimm};

    assign do_read  = en && !(rd_zero        && (funct3 inside {FUNCT3_CSRRW, FUNCT3_CSRRWI}));
    assign do_write = en && !((uimm == 5'd0) && (funct3 inside {FUNCT3_CSRRS, FUNCT3_CSRRC, FUNCT3_CSRRSI, FUNCT3_CSRRCI}));

    //CSRs
    logic [63:0] cycle_cnt;
    logic [63:0] instret_cnt;
    logic        mstatus_mie_q;
    logic        mstatus_mpie_q;
    logic [31:2] mtvec_base_q;
    logic [31:0] mscratch_q;
    logic [31:2] mepc_base_q;
    logic [31:0] mcause_q;
    logic [31:0] mtval_q;
    logic [31:0] csr_val;
    logic        csr_valid;
    logic        csr_ro;

    assign mtvec_out = {mtvec_base_q, 2'b00};
    assign mepc_out  = {mepc_base_q, 2'b00};

    always_comb begin
        csr_valid = 1'b1;
        case (csr_addr)
            CSR_CYCLE,    CSR_MCYCLE:    csr_val = cycle_cnt[31:0];
            CSR_CYCLEH,   CSR_MCYCLEH:   csr_val = cycle_cnt[63:32];
            CSR_TIME:                    csr_val = cycle_cnt[31:0];
            CSR_TIMEH:                   csr_val = cycle_cnt[63:32];
            CSR_INSTRET,  CSR_MINSTRET:  csr_val = instret_cnt[31:0];
            CSR_INSTRETH, CSR_MINSTRETH: csr_val = instret_cnt[63:32];
            CSR_MSTATUS:                 csr_val = {19'b0, 2'b11, 3'b0, mstatus_mpie_q, 3'b0, mstatus_mie_q, 3'b0};
            CSR_MISA:                    csr_val = MISA_RV32IM;
            CSR_MTVEC:                   csr_val = mtvec_out;
            CSR_MSCRATCH:                csr_val = mscratch_q;
            CSR_MEPC:                    csr_val = mepc_out;
            CSR_MCAUSE:                  csr_val = mcause_q;
            CSR_MTVAL:                   csr_val = mtval_q;
            CSR_MVENDORID,
            CSR_MARCHID,
            CSR_MIMPID,
            CSR_MHARTID:                 csr_val = 32'd0;
            default: begin
                csr_val   = 32'd0;
                csr_valid = 1'b0;
            end
        endcase
    end

    assign csr_ro      = (csr_addr[11:10] == CSR_RO_PREFIX);
    assign illegal_csr = en && (!csr_valid || (do_write && csr_ro));
    assign rdata       = do_read ? csr_val : 32'd0;

    logic [31:0] wdata;
    always_comb begin
        case (funct3)
            FUNCT3_CSRRW, FUNCT3_CSRRWI: wdata = source;
            FUNCT3_CSRRS, FUNCT3_CSRRSI: wdata = csr_val | source;
            FUNCT3_CSRRC, FUNCT3_CSRRCI: wdata = csr_val & ~source;
            default:                     wdata = csr_val;
        endcase
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            cycle_cnt      <= 64'd0;
            instret_cnt    <= 64'd0;
            mstatus_mie_q  <= 1'b0;
            mstatus_mpie_q <= 1'b0;
            mtvec_base_q   <= 30'd0;
            mscratch_q     <= 32'd0;
            mepc_base_q    <= 30'd0;
            mcause_q       <= 32'd0;
            mtval_q        <= 32'd0;
        end else begin
            // Software write to mcycle/mcycleh takes priority over +1
            if (do_write && (csr_addr == CSR_MCYCLE)) begin
                cycle_cnt <= {cycle_cnt[63:32], wdata};
            end else if (do_write && (csr_addr == CSR_MCYCLEH)) begin
                cycle_cnt <= {wdata, cycle_cnt[31:0]};
            end else begin
                cycle_cnt <= cycle_cnt + 64'd1;
            end

            // Software write to minstret/minstreth takes priority over +1
            if (do_write && (csr_addr == CSR_MINSTRET)) begin
                instret_cnt <= {instret_cnt[63:32], wdata};
            end else if (do_write && (csr_addr == CSR_MINSTRETH)) begin
                instret_cnt <= {wdata, instret_cnt[31:0]};
            end else if (instret_inc) begin
                instret_cnt <= instret_cnt + 64'd1;
            end

            if (trap_en) begin
                mstatus_mpie_q <= mstatus_mie_q;
                mstatus_mie_q  <= 1'b0;
                mepc_base_q    <= trap_pc_base;
                mcause_q       <= trap_cause;
                mtval_q        <= trap_val;
            end else if (mret_en) begin
                mstatus_mie_q  <= mstatus_mpie_q;
                mstatus_mpie_q <= 1'b1;
            end else if (do_write) begin
                case (csr_addr)
                    CSR_MSTATUS: begin
                        mstatus_mie_q  <= wdata[3];
                        mstatus_mpie_q <= wdata[7];
                    end
                    CSR_MTVEC:    mtvec_base_q <= wdata[31:2];
                    CSR_MSCRATCH: mscratch_q   <= wdata;
                    CSR_MEPC:     mepc_base_q  <= wdata[31:2];
                    CSR_MCAUSE:   mcause_q     <= wdata;
                    CSR_MTVAL:    mtval_q      <= wdata;
                    default: ;
                endcase
            end
        end
    end
endmodule