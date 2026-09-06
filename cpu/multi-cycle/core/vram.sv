module vram #(
	parameter int WORDS = 65536 // 256 KB (2 pages of 128 KB)
)(
	//port a: cpu access
	input  logic        clk_cpu,
	input  logic        en_a,
	input  logic [3:0]  we_a,
	input  logic [15:0] addr_a,
	input  logic [31:0] din_a,
	output logic [31:0] dout_a,

	//port b: vga rasterizer access (read-only)
	input  logic        clk_vga,
	input  logic        en_b,
	input  logic [15:0] addr_b,
	output logic [31:0] dout_b
);
	//256 kb dual-port memory array
	(* ram_style = "block" *) logic [31:0] mem [0:WORDS-1];

	//port a: cpu read/write
	always_ff @(posedge clk_cpu) begin
		if (en_a) begin
			dout_a <= mem[addr_a];
			if (we_a[0]) mem[addr_a][7:0]   <= din_a[7:0];
			if (we_a[1]) mem[addr_a][15:8]  <= din_a[15:8];
			if (we_a[2]) mem[addr_a][23:16] <= din_a[23:16];
			if (we_a[3]) mem[addr_a][31:24] <= din_a[31:24];
		end
	end

	//port b: vga pixel scanner read
	always_ff @(posedge clk_vga) begin
		if (en_b) begin
			dout_b <= mem[addr_b];
		end
	end

endmodule