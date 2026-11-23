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
    
    output logic [31:0] rdata
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
    logic [31:0] mscratch_q;
    logic [31:0] csr_val;

    always_comb begin
        case (csr_addr)
            CSR_CYCLE,    CSR_MCYCLE:    csr_val = cycle_cnt[31:0];
            CSR_CYCLEH,   CSR_MCYCLEH:   csr_val = cycle_cnt[63:32];
            CSR_TIME:                    csr_val = cycle_cnt[31:0];
            CSR_TIMEH:                   csr_val = cycle_cnt[63:32];
            CSR_INSTRET,  CSR_MINSTRET:  csr_val = instret_cnt[31:0];
            CSR_INSTRETH, CSR_MINSTRETH: csr_val = instret_cnt[63:32];
            CSR_MISA:                    csr_val = MISA_RV32IM;
            CSR_MSCRATCH:                csr_val = mscratch_q;
            CSR_MVENDORID,
            CSR_MARCHID,
            CSR_MIMPID,
            CSR_MHARTID:                 csr_val = 32'd0;
            default:                     csr_val = 32'd0;
        endcase
    end

    assign rdata = do_read ? csr_val : 32'd0;

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
            cycle_cnt   <= 64'd0;
            instret_cnt <= 64'd0;
            mscratch_q  <= 32'd0;
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

            if (do_write && (csr_addr == CSR_MSCRATCH)) begin
                mscratch_q <= wdata;
            end
        end
    end
endmodule