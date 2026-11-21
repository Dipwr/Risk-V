import rv32_pkg::*;

module soc_top #(
	parameter string       BOOT_HEX     = "",
	parameter logic [31:0] RESET_PC     = 32'h0000_0000,
	parameter int          CPU_CLK_FREQ = 25_000_000,
	parameter int          UART_BAUD    = 115_200
)(
	input logic clk_cpu,    // cpu clock (e.g. 50 mhz or 100 mhz)
	input logic clk_vga,    // 83.46 mhz pixel clock from clk_wiz_0
	input logic rst_cpu,    // synchronous reset in clk_cpu domain
	input logic rst_vga,    // synchronous reset in clk_vga domain

	//physical pmod vga pins
	output logic        vga_hs,
	output logic        vga_vs,
	output logic [3:0]  vga_r,
	output logic [3:0]  vga_g,
	output logic [3:0]  vga_b,

	//physical uart pins
	input  logic        uart_rx,
	output logic        uart_tx
);
	//core memory bus
	logic        mem_req;
	logic [3:0]  mem_wstrb;
	logic [31:0] mem_addr;
	logic [31:0] mem_wdata;
	logic [31:0] mem_rdata;

	//device select lines
	logic is_ram;
	logic is_vram;
	logic is_io;
	logic is_uart;
	logic is_vga_ctl;

	assign is_ram     = (mem_addr[31:28] == 4'h0);        // 0x0000_0000 - 0x0003_ffff (256 kb)
	assign is_vram    = (mem_addr[31:28] == 4'h1);        // 0x1000_0000 - 0x1003_ffff (256 kb)
	assign is_io      = (mem_addr[31:8]  == 24'h2000_00); // 0x2000_0000 - 0x2000_00ff
	assign is_uart    = is_io && (mem_addr[7:3] == 5'd0); // 0x2000_0000 - 0x2000_0007
	assign is_vga_ctl = is_io && (mem_addr[7:0] == 8'h08);// 0x2000_0008

	//memory enables
	logic ram_en;
	logic vram_en;

	assign ram_en  = mem_req && is_ram;
	assign vram_en = mem_req && is_vram;

	//memory output wires
	logic [31:0] ram_dout;
	logic [31:0] vram_dout;
	logic [31:0] io_dout;

	//16-bit word addresses (mem_addr[17:2])
	logic [15:0] ram_word_addr;
	logic [15:0] vram_word_addr;

	assign ram_word_addr  = mem_addr[17:2];
	assign vram_word_addr = mem_addr[17:2];

	//vga display page mmio register & synced status (0x2000_0008)
	logic vga_display_page;
	logic vga_no_vsync;
	logic vga_vblank;
	logic vga_active_page;
	(* ASYNC_REG = "TRUE" *) logic vblank_sync_1;
	(* ASYNC_REG = "TRUE" *) logic vblank_sync_2;
	(* ASYNC_REG = "TRUE" *) logic active_page_sync_1;
	(* ASYNC_REG = "TRUE" *) logic active_page_sync_2;

	always_ff @(posedge clk_cpu) begin
		if (rst_cpu) begin
			vga_display_page   <= 1'b0;
			vga_no_vsync       <= 1'b0;
			vblank_sync_1      <= 1'b0;
			vblank_sync_2      <= 1'b0;
			active_page_sync_1 <= 1'b0;
			active_page_sync_2 <= 1'b0;
		end else begin
			vblank_sync_1      <= vga_vblank;
			vblank_sync_2      <= vblank_sync_1;
			active_page_sync_1 <= vga_active_page;
			active_page_sync_2 <= active_page_sync_1;
			if (mem_req && is_vga_ctl && (|mem_wstrb)) begin
				vga_display_page <= mem_wdata[0];
				vga_no_vsync     <= mem_wdata[1];
			end
		end
	end

	//real uart module instance
	logic [31:0] uart_rdata;
	logic        uart_we;
	logic        uart_re;

	assign uart_we = mem_req && is_uart && (|mem_wstrb);
	assign uart_re = mem_req && is_uart && (mem_wstrb == 4'b0000);

	uart #(
		.CLK_FREQ      (CPU_CLK_FREQ),
		.BAUD          (UART_BAUD),
		.RX_FIFO_DEPTH (64),
		.TX_FIFO_DEPTH (64)
	) u_uart (
		.clk   (clk_cpu),
		.rst   (rst_cpu),
		.we    (uart_we),
		.re    (uart_re),
		.addr  (mem_addr[3:0]),
		.wdata (mem_wdata),
		.rdata (uart_rdata),
		.rx    (uart_rx),
		.tx    (uart_tx)
	);

	//io read data register (matches 1-cycle bram latency)
	always_ff @(posedge clk_cpu) begin
		if (rst_cpu) begin
			io_dout <= 32'h0000_0000;
		end else if (mem_req && is_io) begin
			if (is_uart) begin
				io_dout <= uart_rdata;                                // uart rx data / status
			end else if (is_vga_ctl) begin
				// [3] no_vsync, [2] active_page, [1] vblank, [0] display_page
				io_dout <= {28'b0, vga_no_vsync, active_page_sync_2, vblank_sync_2, vga_display_page};
			end else begin
				io_dout <= 32'h0000_0000;
			end
		end
	end

	//device response tracker for 1-cycle bram read latency
	typedef enum logic [1:0] {DEV_RAM, DEV_VRAM, DEV_IO, DEV_NONE} dev_sel_t;
	dev_sel_t dev_sel_q;
	always_ff @(posedge clk_cpu) begin
		if (rst_cpu) begin
			dev_sel_q <= DEV_NONE;
		end else if (mem_req) begin
			if (is_ram) begin
				dev_sel_q <= DEV_RAM;
			end else if (is_vram) begin
				dev_sel_q <= DEV_VRAM;
			end else if (is_io) begin
				dev_sel_q <= DEV_IO;
			end else begin
				dev_sel_q <= DEV_NONE;
			end
		end
	end

	//return data multiplexer
	always_comb begin
		case (dev_sel_q)
			DEV_RAM:  mem_rdata = ram_dout;
			DEV_VRAM: mem_rdata = vram_dout;
			DEV_IO:   mem_rdata = io_dout;
			default:  mem_rdata = 32'd0;
		endcase
	end

	//cpu instance
	rv32_core #(
		.RESET_PC (RESET_PC)
	) u_core (
		.clk       (clk_cpu),
		.rst       (rst_cpu),
		.mem_req   (mem_req),
		.mem_wstrb (mem_wstrb),
		.mem_addr  (mem_addr),
		.mem_wdata (mem_wdata),
		.mem_rdata (mem_rdata)
	);

	//main ram instance (256 kb)
	bram_ram #(
		.WORDS     (65536),
		.INIT_FILE (BOOT_HEX)
	) u_ram (
		.clk  (clk_cpu),
		.en   (ram_en),
		.we   (mem_wstrb),
		.addr (ram_word_addr),
		.din  (mem_wdata),
		.dout (ram_dout)
	);

	//internal wires between vram port b and vga controller
	logic        vga_vram_en;
	logic [15:0] vga_vram_addr;
	logic [31:0] vga_vram_data;

	//vram instance (256 kb dual-port)
	vram #(
		.WORDS (65536)
	) u_vram (
		//port a: cpu access
		.clk_cpu (clk_cpu),
		.en_a    (vram_en),
		.we_a    (mem_wstrb),
		.addr_a  (vram_word_addr),
		.din_a   (mem_wdata),
		.dout_a  (vram_dout),

		//port b: vga rasterizer access
		.clk_vga (clk_vga),
		.en_b    (vga_vram_en),
		.addr_b  (vga_vram_addr),
		.dout_b  (vga_vram_data)
	);

	//vga controller instance
	vga_controller u_vga_controller (
		.clk_vga      (clk_vga),
		.rst          (rst_vga),
		.display_page (vga_display_page),
		.no_vsync     (vga_no_vsync),
		.vblank       (vga_vblank),
		.active_page  (vga_active_page),
		.vram_en      (vga_vram_en),
		.vram_addr    (vga_vram_addr),
		.vram_data    (vga_vram_data),
		.vga_hs       (vga_hs),
		.vga_vs       (vga_vs),
		.vga_r        (vga_r),
		.vga_g        (vga_g),
		.vga_b        (vga_b)
	);

endmodule