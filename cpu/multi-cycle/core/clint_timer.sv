module clint_timer #(
    parameter int CPU_CLK_FREQ  = 84_000_000,
    parameter int TIMER_TICK_HZ = 1_000_000
)(
    input  logic        clk,
    input  logic        rst,

    input  logic        we,
    input  logic [3:0]  wstrb,
    input  logic [1:0]  word_addr, // 0: mtime_lo, 1: mtime_hi, 2: mtimecmp_lo, 3: mtimecmp_hi
    input  logic [31:0] wdata,
    output logic [31:0] rdata,

    output logic [63:0] mtime_o,
    output logic        timer_irq_o
);
    localparam int PRESCALE_DIV = (CPU_CLK_FREQ >= TIMER_TICK_HZ) ? (CPU_CLK_FREQ / TIMER_TICK_HZ) : 1;
    localparam int PRESCALE_W   = (PRESCALE_DIV > 1) ? $clog2(PRESCALE_DIV) : 1;

    logic [PRESCALE_W-1:0] prescale_q;
    logic [63:0]           mtime_q;
    logic [63:0]           mtimecmp_q;
    logic                  timer_irq_q;
    logic                  tick_en;

    function automatic logic [31:0] apply_wstrb(
        input logic [31:0] old_val,
        input logic [31:0] new_val,
        input logic [3:0]  mask
    );
        logic [31:0] res;
        res[7:0]   = mask[0] ? new_val[7:0]   : old_val[7:0];
        res[15:8]  = mask[1] ? new_val[15:8]  : old_val[15:8];
        res[23:16] = mask[2] ? new_val[23:16] : old_val[23:16];
        res[31:24] = mask[3] ? new_val[31:24] : old_val[31:24];
        return res;
    endfunction

    if (PRESCALE_DIV <= 1) begin : gen_no_prescale
        assign tick_en = 1'b1;
    end else begin : gen_prescale
        assign tick_en = (prescale_q == PRESCALE_W'(PRESCALE_DIV - 1));
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            prescale_q  <= '0;
            mtime_q     <= 64'd0;
            mtimecmp_q  <= 64'hFFFF_FFFF_FFFF_FFFF;
            timer_irq_q <= 1'b0;
        end else begin
            // Prescaler counter
            if (PRESCALE_DIV > 1) begin
                prescale_q <= tick_en ? '0 : (prescale_q + PRESCALE_W'(1));
            end

            // mtime: software write takes priority over +1 tick
            if (we && (|wstrb) && (word_addr == 2'd0)) begin
                mtime_q <= {mtime_q[63:32], apply_wstrb(mtime_q[31:0], wdata, wstrb)};
            end else if (we && (|wstrb) && (word_addr == 2'd1)) begin
                mtime_q <= {apply_wstrb(mtime_q[63:32], wdata, wstrb), mtime_q[31:0]};
            end else if (tick_en) begin
                mtime_q <= mtime_q + 64'd1;
            end

            // mtimecmp
            if (we && (|wstrb) && (word_addr == 2'd2)) begin
                mtimecmp_q <= {mtimecmp_q[63:32], apply_wstrb(mtimecmp_q[31:0], wdata, wstrb)};
            end else if (we && (|wstrb) && (word_addr == 2'd3)) begin
                mtimecmp_q <= {apply_wstrb(mtimecmp_q[63:32], wdata, wstrb), mtimecmp_q[31:0]};
            end

            // Registered 64-bit comparator output to isolate carry chain from CPU STA
            timer_irq_q <= (mtime_q >= mtimecmp_q);
        end
    end

    always_comb begin
        case (word_addr)
            2'd0:    rdata = mtime_q[31:0];
            2'd1:    rdata = mtime_q[63:32];
            2'd2:    rdata = mtimecmp_q[31:0];
            2'd3:    rdata = mtimecmp_q[63:32];
        endcase
    end

    assign mtime_o     = mtime_q;
    assign timer_irq_o = timer_irq_q;
endmodule
