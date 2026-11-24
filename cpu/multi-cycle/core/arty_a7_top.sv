module arty_a7_top #(
	parameter string       BOOT_HEX     = "boot.mem",
	parameter logic [31:0] RESET_PC     = 32'h0000_0000,
	parameter int          CPU_CLK_FREQ = 84_000_000,
	parameter int          UART_BAUD    = 115_200
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
	//clock wizard outputs (separate CPU and VGA MMCM/PLL instances)
	logic clk_cpu;
	logic clk_vga;
	logic clk_cpu_locked;
	logic clk_vga_locked;
	logic clk_locked;

	//keep clock wizards running continuously so BTN0 never stops or glitches clocks
	clk_wiz_0 u_clk_wiz_cpu (
		.clk_in1  (CLK100MHZ),
		.clk_out1 (clk_cpu),     // cpu clock (matches CPU_CLK_FREQ)
		.reset    (1'b0),
		.locked   (clk_cpu_locked)
	);

	clk_wiz_1 u_clk_wiz_vga (
		.clk_in1  (CLK100MHZ),
		.clk_out1 (clk_vga),     // 83.46 mhz pixel clock
		.reset    (1'b0),
		.locked   (clk_vga_locked)
	);

	assign clk_locked = clk_cpu_locked && clk_vga_locked;

	//raw async reset asserted on BTN0 press or while pll is unlocked
	logic async_rst;
	assign async_rst = btn_rst || !clk_locked;

	//per-domain reset synchronizers: async-assert on all stages + sync deassert
	(* ASYNC_REG = "TRUE" *) logic [1:0] cpu_rst_sync = 2'b11;
	(* ASYNC_REG = "TRUE" *) logic [1:0] vga_rst_sync = 2'b11;
	logic rst_cpu = 1'b1;
	logic rst_vga = 1'b1;

	always_ff @(posedge clk_cpu or posedge async_rst) begin
		if (async_rst) begin
			cpu_rst_sync <= 2'b11;
			rst_cpu      <= 1'b1;
		end else begin
			cpu_rst_sync <= {cpu_rst_sync[0], 1'b0};
			rst_cpu      <= cpu_rst_sync[1];
		end
	end

	always_ff @(posedge clk_vga or posedge async_rst) begin
		if (async_rst) begin
			vga_rst_sync <= 2'b11;
			rst_vga      <= 1'b1;
		end else begin
			vga_rst_sync <= {vga_rst_sync[0], 1'b0};
			rst_vga      <= vga_rst_sync[1];
		end
	end

	//soc top instance
	soc_top #(
		.BOOT_HEX     (BOOT_HEX),
		.RESET_PC     (RESET_PC),
		.CPU_CLK_FREQ (CPU_CLK_FREQ),
		.UART_BAUD    (UART_BAUD)
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
