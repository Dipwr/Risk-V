module arty_a7_top #(
	parameter string       BOOT_HEX = "boot.mem",
	parameter logic [31:0] RESET_PC = 32'h0000_0000
)(
	input  logic       CLK100MHZ,    // pin E3 (100 mhz crystal oscillator)
	input  logic       btn_rst,      // pin D9 (BTN0 push button, active-high)

	//pmod vga pins (headers jb & jc)
	output logic       vga_hs,
	output logic       vga_vs,
	output logic [3:0] vga_r,
	output logic [3:0] vga_g,
	output logic [3:0] vga_b,

	//usb-uart bridge pins (corrected direction)
	input  logic       uart_rx_pin,  // pin A9  (PC TX -> FPGA RX)
	output logic       uart_tx_pin   // pin D10 (FPGA TX -> PC RX)
);
	//clock wizard outputs
	logic clk_cpu;
	logic clk_vga;
	logic clk_locked;

	//clocking wizard instance (requires raw asynchronous reset from BTN0)
	clk_wiz_0 u_clk_wiz (
		.clk_in1  (CLK100MHZ),
		.clk_out1 (clk_cpu),     // 25 mhz cpu clock
		.clk_out2 (clk_vga),     // 83.46 mhz pixel clock
		.reset    (btn_rst),
		.locked   (clk_locked)
	);

	//raw async reset asserted on BTN0 press or while pll is unlocked
	logic async_rst;
	assign async_rst = btn_rst || !clk_locked;

	//per-domain reset synchronizers: async-assert 2-ff CDC bridge + sync fanout stage
	(* ASYNC_REG = "TRUE" *) logic [1:0] cpu_rst_sync = 2'b11;
	(* ASYNC_REG = "TRUE" *) logic [1:0] vga_rst_sync = 2'b11;
	logic rst_cpu = 1'b1;
	logic rst_vga = 1'b1;

	always_ff @(posedge clk_cpu or posedge async_rst) begin
		if (async_rst) begin
			cpu_rst_sync <= 2'b11;
		end else begin
			cpu_rst_sync <= {cpu_rst_sync[0], 1'b0};
		end
	end

	always_ff @(posedge clk_cpu) begin
		rst_cpu <= cpu_rst_sync[1];
	end

	always_ff @(posedge clk_vga or posedge async_rst) begin
		if (async_rst) begin
			vga_rst_sync <= 2'b11;
		end else begin
			vga_rst_sync <= {vga_rst_sync[0], 1'b0};
		end
	end

	always_ff @(posedge clk_vga) begin
		rst_vga <= vga_rst_sync[1];
	end

	//soc top instance
	soc_top #(
		.BOOT_HEX (BOOT_HEX),
		.RESET_PC (RESET_PC)
	) u_soc_top (
		.clk_cpu (clk_cpu),
		.clk_vga (clk_vga),
		.rst_cpu (rst_cpu),
		.rst_vga (rst_vga),
		.vga_hs  (vga_hs),
		.vga_vs  (vga_vs),
		.vga_r   (vga_r),
		.vga_g   (vga_g),
		.vga_b   (vga_b),
		.uart_rx (uart_rx_pin),
		.uart_tx (uart_tx_pin)
	);

endmodule