// Behavioral CPU Clocking Wizard stub for Verilator simulation of arty_a7_top.
// sim_clk_cpu is driven directly from sim_main.cpp via sim.vlt.
module clk_wiz_0 (
	input  logic clk_in1,
	output logic clk_out1,
	input  logic reset,
	output logic locked
);
	logic sim_clk_cpu = 1'b0;

	logic [2:0] lock_cnt = 3'd0;

	always_ff @(posedge clk_in1 or posedge reset) begin
		if (reset) begin
			lock_cnt <= 3'd0;
			locked   <= 1'b0;
		end else if (lock_cnt != 3'd7) begin
			lock_cnt <= lock_cnt + 3'd1;
			locked   <= 1'b0;
		end else begin
			locked   <= 1'b1;
		end
	end

	assign clk_out1 = sim_clk_cpu;

endmodule
