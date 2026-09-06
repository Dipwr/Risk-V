module bram_ram #(
	parameter int    WORDS     = 65536, // 256 KB
	parameter string INIT_FILE = ""
)(
	input  logic        clk,
	input  logic        en,
	input  logic [3:0]  we,
	input  logic [15:0] addr,
	input  logic [31:0] din,
	output logic [31:0] dout
);
	//256 kb memory array
	(* ram_style = "block" *) logic [31:0] mem [0:WORDS-1];

	//optional bitstream pre-initialization
	initial begin
		if (INIT_FILE != "") begin
			$readmemh(INIT_FILE, mem);
		end
	end

	//synchronous b-ram read/write
	always_ff @(posedge clk) begin
		if (en) begin
			dout <= mem[addr];
			if (we[0]) mem[addr][7:0]   <= din[7:0];
			if (we[1]) mem[addr][15:8]  <= din[15:8];
			if (we[2]) mem[addr][23:16] <= din[23:16];
			if (we[3]) mem[addr][31:24] <= din[31:24];
		end
	end

endmodule