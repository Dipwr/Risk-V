module vga_controller (
	input  logic        clk_vga,    // 83.46 mhz from clk_wiz_0
	input  logic        rst,

	//double buffering page selector (0: page 0, 1: page 1)
	input  logic        display_page,

	//vram port b interface
	output logic        vram_en,
	output logic [15:0] vram_addr,
	input  logic [31:0] vram_data,

	//physical vga output pins
	output logic        vga_hs,
	output logic        vga_vs,
	output logic [3:0]  vga_r,
	output logic [3:0]  vga_g,
	output logic [3:0]  vga_b
);
	//vesa 1280x800 @ 60hz cvt timing parameters
	localparam int H_ACTIVE = 1280;
	localparam int H_FP     = 64;
	localparam int H_SYNC   = 136;
	localparam int H_BP     = 200;
	localparam int H_TOTAL  = 1680;

	localparam int V_ACTIVE = 800;
	localparam int V_FP     = 1;
	localparam int V_SYNC   = 3;
	localparam int V_BP     = 24;
	localparam int V_TOTAL  = 828;

	//timing counters
	logic [10:0] h_count;
	logic [9:0]  v_count;

	always_ff @(posedge clk_vga or posedge rst) begin
		if (rst) begin
			h_count <= 11'd0;
			v_count <= 10'd0;
		end else begin
			if (h_count == H_TOTAL - 1) begin
				h_count <= 11'd0;
				if (v_count == V_TOTAL - 1) begin
					v_count <= 10'd0;
				end else begin
					v_count <= v_count + 10'd1;
				end
			end else begin
				h_count <= h_count + 11'd1;
			end
		end
	end

	//raw sync and active video signals
	logic raw_hs;
	logic raw_vs;
	logic raw_active;

	//horizontal sync is negative (active low)
	assign raw_hs     = ~((h_count >= (H_ACTIVE + H_FP)) && (h_count < (H_ACTIVE + H_FP + H_SYNC)));
	//vertical sync is positive (active high)
	assign raw_vs     =  ((v_count >= (V_ACTIVE + V_FP)) && (v_count < (V_ACTIVE + V_FP + V_SYNC)));
	assign raw_active =  (h_count < H_ACTIVE) && (v_count < V_ACTIVE);

	//4x scaling down to 320x200 frame buffer
	logic [8:0] fb_x;
	logic [7:0] fb_y;

	assign fb_x = h_count[10:2]; // h_count / 4 (0 to 319)
	assign fb_y = v_count[9:2];  // v_count / 4 (0 to 199)

	//multiplier-free pixel index: (fb_y * 256) + (fb_y * 64) + fb_x
	logic [15:0] pixel_index;
	assign pixel_index = {fb_y, 8'b0} + {2'b0, fb_y, 6'b0} + {7'b0, fb_x};

	//synchronize display_page into vga clock domain
	(* ASYNC_REG = "TRUE" *) logic page_sync_1;
	(* ASYNC_REG = "TRUE" *) logic page_sync_2;

	always_ff @(posedge clk_vga or posedge rst) begin
		if (rst) begin
			page_sync_1 <= 1'b0;
			page_sync_2 <= 1'b0;
		end else begin
			page_sync_1 <= display_page;
			page_sync_2 <= page_sync_1;
		end
	end

	//vram word address and page base offset
	assign vram_en   = raw_active;
	assign vram_addr = (page_sync_2 ? 16'd32768 : 16'd0) + (pixel_index >> 1);

	//pipeline registers to match 1-cycle bram read latency
	logic        pipe_hs;
	logic        pipe_vs;
	logic        pipe_active;
	logic        pixel_sel_q;

	always_ff @(posedge clk_vga or posedge rst) begin
		if (rst) begin
			pipe_hs     <= 1'b1;
			pipe_vs     <= 1'b0;
			pipe_active <= 1'b0;
			pixel_sel_q <= 1'b0;
		end else begin
			pipe_hs     <= raw_hs;
			pipe_vs     <= raw_vs;
			pipe_active <= raw_active;
			pixel_sel_q <= fb_x[0]; // remember which halfword was requested
		end
	end

	//16-bit rgb565 pixel demux from 32-bit vram word
	logic [15:0] current_pixel;
	assign current_pixel = (pixel_sel_q == 1'b0) ? vram_data[15:0] : vram_data[31:16];

	//color mapping: rgb565 to rgb444 (pmod vga dac)
	assign vga_hs = pipe_hs;
	assign vga_vs = pipe_vs;

	assign vga_r  = pipe_active ? current_pixel[15:12] : 4'h0;
	assign vga_g  = pipe_active ? current_pixel[10:7]  : 4'h0;
	assign vga_b  = pipe_active ? current_pixel[4:1]   : 4'h0;

endmodule