#include <stdint.h>

/* --- Memory-Mapped I/O Registers --- */
#define PAGE_REG     ((volatile uint32_t *)0x00080000)
#define TERM_OUT     ((volatile uint32_t *)0x00080004)
#define KEY_DATA     ((volatile uint32_t *)0x00080020)
#define KEY_STAT     ((volatile uint32_t *)0x00080024)

/* 16-bit Packed VRAM Pointer (1 pixel per 2 bytes) */
#define GRAPHIC_RAM  ((volatile uint16_t *)0x00082000)

/* --- Display & Viewport Setup --- */
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS   (SCREEN_WIDTH * SCREEN_HEIGHT) // 64,000 pixels per page

#define GRID_W 64
#define GRID_H 40
#define GRID_SIZE (GRID_W * GRID_H)
#define CELL_SIZE 4

#define OFFSET_X ((SCREEN_WIDTH - (GRID_W * CELL_SIZE)) / 2)  // 32 px margin
#define OFFSET_Y ((SCREEN_HEIGHT - (GRID_H * CELL_SIZE)) / 2) // 20 px margin

/* --- Color Palette (RGB565 format: 5-bit Red, 6-bit Green, 5-bit Blue) --- */
#define MAKE_RGB(r, g, b) ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define COLOR_BG     ((uint16_t)0x0000)                 // Pure Black
#define COLOR_BORDER MAKE_RGB(15, 31, 31)               // Bright bluish-gray frame
#define COLOR_ALIVE  MAKE_RGB(0, 63, 10)                // High-visibility Lime Green
#define COLOR_DEAD   MAKE_RGB(2, 8, 8)                  // Dark slate background cell

/* --- Software Math Helpers (RV32I -nostdlib) --- */
int __mulsi3(int a, int b) {
	int res = 0;
	int neg = (a < 0) ^ (b < 0);
	unsigned int ua = (a < 0) ? -a : a;
	unsigned int ub = (b < 0) ? -b : b;
	while (ub > 0) {
		if (ub & 1) res += ua;
		ua <<= 1;
		ub >>= 1;
	}
	return neg ? -res : res;
}

int __divsi3(int a, int b) {
	if (b == 0) return 0;
	int neg = (a < 0) ^ (b < 0);
	unsigned int num = (a < 0) ? -a : a;
	unsigned int den = (b < 0) ? -b : b;
	unsigned int quot = 0, rem = 0;
	for (int i = 31; i >= 0; i--) {
		rem = (rem << 1) | ((num >> i) & 1);
		if (rem >= den) {
			rem -= den;
			quot |= (1U << i);
		}
	}
	return neg ? -(int)quot : (int)quot;
}

int __modsi3(int a, int b) {
	if (b == 0) return 0;
	int q = __divsi3(a, b);
	return a - __mulsi3(q, b);
}

uint32_t __udivsi3(uint32_t num, uint32_t den) {
	if (den == 0) return 0;
	uint32_t quot = 0, rem = 0;
	for (int i = 31; i >= 0; i--) {
		rem = (rem << 1) | ((num >> i) & 1);
		if (rem >= den) {
			rem -= den;
			quot |= (1U << i);
		}
	}
	return quot;
}

uint32_t __umodsi3(uint32_t num, uint32_t den) {
	if (den == 0) return 0;
	uint32_t rem = 0;
	for (int i = 31; i >= 0; i--) {
		rem = (rem << 1) | ((num >> i) & 1);
		if (rem >= den) {
			rem -= den;
		}
	}
	return rem;
}

/* --- Terminal Output Helper --- */
void print_string(const char *str) {
	while (*str) {
		*TERM_OUT = (uint32_t)(*str++);
	}
}

/* 8-bit Byte Grid Arrays */
static uint8_t grid[GRID_SIZE];
static uint8_t next_grid[GRID_SIZE];
static uint32_t current_seed = 0x1337BEEF;

/* SplitMix32 Bit Mixer */
static uint32_t proper_hash(int x, int y, uint32_t seed) {
	uint32_t h = (uint32_t)__mulsi3(x, 0x1F3D) + (uint32_t)__mulsi3(y, 0x3079) + seed;
	h ^= h >> 16;
	h = (uint32_t)__mulsi3((int)h, (int)0x85ebca6b);
	h ^= h >> 13;
	h = (uint32_t)__mulsi3((int)h, (int)0xc2b2ae35);
	h ^= h >> 16;
	return h;
}

static inline void set_cell(int x, int y, uint8_t val) {
	if (x >= 0 && x < GRID_W && y >= 0 && y < GRID_H) {
		grid[(y * GRID_W) + x] = val;
	}
}

/* --- Graphics Rendering Routines --- */
void clear_page(int page, uint16_t color) {
	uint32_t offset = page * PAGE_PIXELS;
	for (int i = 0; i < PAGE_PIXELS; i++) {
		GRAPHIC_RAM[offset + i] = color;
	}
}

void draw_frame_border(int page) {
	uint32_t page_offset = page * PAGE_PIXELS;
	int min_x = OFFSET_X - 1;
	int max_x = OFFSET_X + (GRID_W * CELL_SIZE);
	int min_y = OFFSET_Y - 1;
	int max_y = OFFSET_Y + (GRID_H * CELL_SIZE);

	for (int x = min_x; x <= max_x; x++) {
		GRAPHIC_RAM[page_offset + (min_y * SCREEN_WIDTH) + x] = COLOR_BORDER;
		GRAPHIC_RAM[page_offset + (max_y * SCREEN_WIDTH) + x] = COLOR_BORDER;
	}
	for (int y = min_y; y <= max_y; y++) {
		GRAPHIC_RAM[page_offset + (y * SCREEN_WIDTH) + min_x] = COLOR_BORDER;
		GRAPHIC_RAM[page_offset + (y * SCREEN_WIDTH) + max_x] = COLOR_BORDER;
	}
}

void render_grid(int page) {
	uint32_t page_offset = page * PAGE_PIXELS;

	for (int y = 0; y < GRID_H; y++) {
		int py = OFFSET_Y + (y * CELL_SIZE);
		int row_idx = y * GRID_W;

		for (int x = 0; x < GRID_W; x++) {
			int px = OFFSET_X + (x * CELL_SIZE);
			uint16_t color = grid[row_idx + x] ? COLOR_ALIVE : COLOR_DEAD;

			for (int dy = 0; dy < CELL_SIZE; dy++) {
				uint32_t screen_row = page_offset + ((py + dy) * SCREEN_WIDTH) + px;
				for (int dx = 0; dx < CELL_SIZE; dx++) {
					GRAPHIC_RAM[screen_row + dx] = color;
				}
			}
		}
	}
}

/* --- Conway Logic --- */
int count_neighbors(int y, int x) {
	int count = 0;

	for (int dy = -1; dy <= 1; dy++) {
		int ny = y + dy;
		if (ny < 0) ny = GRID_H - 1;
		else if (ny >= GRID_H) ny = 0;

		int ny_offset = ny * GRID_W;

		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) continue;

			int nx = x + dx;
			if (nx < 0) nx = GRID_W - 1;
			else if (nx >= GRID_W) nx = 0;

			if (grid[ny_offset + nx]) count++;
		}
	}
	return count;
}

void update_life(void) {
	for (int y = 0; y < GRID_H; y++) {
		int row_idx = y * GRID_W;
		for (int x = 0; x < GRID_W; x++) {
			int idx = row_idx + x;
			int neighbors = count_neighbors(y, x);

			if (grid[idx]) {
				next_grid[idx] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
			} else {
				next_grid[idx] = (neighbors == 3) ? 1 : 0;
			}
		}
	}

	for (int i = 0; i < GRID_SIZE; i++) {
		grid[i] = next_grid[i];
	}
}

/* --- Seed Generators --- */
void seed_grid_random(uint32_t seed) {
	for (int y = 0; y < GRID_H; y++) {
		int row_idx = y * GRID_W;
		for (int x = 0; x < GRID_W; x++) {
			grid[row_idx + x] = ((proper_hash(x, y, seed) & 0xFF) < 90) ? 1 : 0;
		}
	}
}

void seed_grid_patterns(void) {
	for (int i = 0; i < GRID_SIZE; i++) grid[i] = 0;

	// Gosper Glider Gun (Top Left)
	int gx = 1, gy = 1;
	set_cell(gx+24, gy+0, 1);
	set_cell(gx+22, gy+1, 1); set_cell(gx+24, gy+1, 1);
	set_cell(gx+12, gy+2, 1); set_cell(gx+13, gy+2, 1); set_cell(gx+20, gy+2, 1); set_cell(gx+21, gy+2, 1); set_cell(gx+34, gy+2, 1); set_cell(gx+35, gy+2, 1);
	set_cell(gx+11, gy+3, 1); set_cell(gx+15, gy+3, 1); set_cell(gx+20, gy+3, 1); set_cell(gx+21, gy+3, 1); set_cell(gx+34, gy+3, 1); set_cell(gx+35, gy+3, 1);
	set_cell(gx+0,  gy+4, 1); set_cell(gx+1,  gy+4, 1); set_cell(gx+10, gy+4, 1); set_cell(gx+16, gy+4, 1); set_cell(gx+20, gy+4, 1); set_cell(gx+21, gy+4, 1);
	set_cell(gx+0,  gy+5, 1); set_cell(gx+1,  gy+5, 1); set_cell(gx+10, gy+5, 1); set_cell(gx+14, gy+5, 1); set_cell(gx+16, gy+5, 1); set_cell(gx+17, gy+5, 1); set_cell(gx+22, gy+5, 1); set_cell(gx+24, gy+5, 1);
	set_cell(gx+10, gy+6, 1); set_cell(gx+16, gy+6, 1); set_cell(gx+24, gy+6, 1);
	set_cell(gx+11, gy+7, 1); set_cell(gx+15, gy+7, 1);
	set_cell(gx+12, gy+8, 1); set_cell(gx+13, gy+8, 1);

	// Acorn Methuselah (Center)
	int ax = 28, ay = 25;
	set_cell(ax+1, ay+0, 1);
	set_cell(ax+3, ay+1, 1);
	set_cell(ax+0, ay+2, 1); set_cell(ax+1, ay+2, 1); set_cell(ax+4, ay+2, 1); set_cell(ax+5, ay+2, 1); set_cell(ax+6, ay+2, 1);

	// Pulsar Oscillator (Right Side)
	int px = 46, py = 12;
	for (int i = 0; i < 3; i++) {
		set_cell(px+2+i, py+0, 1); set_cell(px+8+i, py+0, 1);
		set_cell(px+2+i, py+5, 1); set_cell(px+8+i, py+5, 1);
		set_cell(px+2+i, py+7, 1); set_cell(px+8+i, py+7, 1);
		set_cell(px+2+i, py+12, 1); set_cell(px+8+i, py+12, 1);
	}
	for (int j = 0; j < 3; j++) {
		set_cell(px+0, py+2+j, 1); set_cell(px+5, py+2+j, 1); set_cell(px+7, py+2+j, 1); set_cell(px+12, py+2+j, 1);
		set_cell(px+0, py+8+j, 1); set_cell(px+5, py+8+j, 1); set_cell(px+7, py+8+j, 1); set_cell(px+12, py+8+j, 1);
	}

	// Lightweight Spaceship (Bottom Left)
	int lx = 3, ly = 32;
	set_cell(lx+1, ly+0, 1); set_cell(lx+4, ly+0, 1);
	set_cell(lx+0, ly+1, 1);
	set_cell(lx+0, ly+2, 1); set_cell(lx+4, ly+2, 1);
	set_cell(lx+0, ly+3, 1); set_cell(lx+1, ly+3, 1); set_cell(lx+2, ly+3, 1); set_cell(lx+3, ly+3, 1);
}

void setup_display(void) {
	clear_page(0, COLOR_BG);
	clear_page(1, COLOR_BG);
	draw_frame_border(0);
	draw_frame_border(1);
}

/* --- Main Program --- */
int main(void) {
	print_string("[RV32I Core] Conway's Game of Life (16-bit RGB565)\n");
	print_string("Controls: [P/Space] Pause | [N] Step | [R] Random Seed | [S] Preset | [Q/ESC] Quit\n");

	seed_grid_random(current_seed);
	setup_display();

	uint32_t active_page = 0;
	int paused = 0;
	int step_once = 0;
	int running = 1;

	render_grid(0);
	render_grid(1);

	while (running) {
		while (*KEY_STAT != 0) {
			char key = (char)(*KEY_DATA & 0xFF);
			current_seed += (uint32_t)key;

			if (key == 'p' || key == 'P' || key == ' ') {
				paused = !paused;
				print_string(paused ? "[Paused]\n" : "[Running]\n");
			} else if (key == 'n' || key == 'N') {
				step_once = 1;
				print_string("[Next Step]\n");
			} else if (key == 'r' || key == 'R') {
				current_seed += 0x9E3779B9;
				seed_grid_random(current_seed);
				paused = 1;
				step_once = 0;
				render_grid(0);
				render_grid(1);
				print_string("[New Universe Generated & Paused]\n");
			} else if (key == 's' || key == 'S') {
				seed_grid_patterns();
				paused = 1;
				step_once = 0;
				render_grid(0);
				render_grid(1);
				print_string("[Structure Preset Loaded & Paused]\n");
			} else if (key == 'q' || key == 'Q' || key == 27) { // 27 = ESC
				running = 0;
				print_string("[Exiting to Wozmon...]\n");
				break;
			}
		}

		if (!running) break;

		if (!paused || step_once) {
			update_life();
			step_once = 0;
		}

		uint32_t back_page = 1 - active_page;
		render_grid(back_page);
		*PAGE_REG = back_page;
		active_page = back_page;

		for (volatile int delay = 0; delay < 30000; delay++);
	}

	*PAGE_REG = 0;
	void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
	wozmon_entry();

	return 0;
}