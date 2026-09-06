module arty_a7_top (
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
	//direct active-high reset from BTN0
	logic rst;
	assign rst = btn_rst;

	//clock wizard outputs
	logic clk_cpu;
	logic clk_vga;
	logic clk_locked;

	//clocking wizard instance
	clk_wiz_0 u_clk_wiz (
		.clk_in1  (CLK100MHZ),
		.clk_out1 (clk_cpu),     // 25 mhz cpu clock
		.clk_out2 (clk_vga),     // 83.46 mhz pixel clock
		.reset    (rst),
		.locked   (clk_locked)
	);

	//hold soc in reset until pll is locked
	logic sys_rst;
	assign sys_rst = rst || !clk_locked;

	//soc top instance
	soc_top #(
		.BOOT_HEX ("boot.mem")
	) u_soc_top (
		.clk_cpu (clk_cpu),
		.clk_vga (clk_vga),
		.rst     (sys_rst),
		.vga_hs  (vga_hs),
		.vga_vs  (vga_vs),
		.vga_r   (vga_r),
		.vga_g   (vga_g),
		.vga_b   (vga_b),
		.uart_rx (uart_rx_pin),
		.uart_tx (uart_tx_pin)
	);

endmodule