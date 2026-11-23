#include "bsp.h"
#include <stdint.h>

/* 16-word callee-saved register save area used by riscv_test.h */
uint32_t rvtest_saved_regs[16];

typedef enum {
	SUITE_UI = 0,
	SUITE_UM = 1,
	SUITE_MI = 2
} suite_id_t;

typedef struct {
	suite_id_t suite;
	const char *suite_name;
	const char *name;
	const char *short_name;
	uint32_t (*fn)(void);
} compliance_test_t;

#include "test_table.h"

/* RGB565 colors */
#define C_BG      ((uint16_t)0x0842)
#define C_HEADER  ((uint16_t)0x10A6)
#define C_BORDER  ((uint16_t)0x4228)
#define C_PENDING ((uint16_t)0x2104)
#define C_RUNNING ((uint16_t)0xFD20)
#define C_PASS    ((uint16_t)0x05E0)
#define C_FAIL    ((uint16_t)0xD800)
#define C_WHITE   ((uint16_t)0xFFFF)
#define C_CYAN    ((uint16_t)0x5FFF)
#define C_GRAY    ((uint16_t)0xBDF7)
#define C_BLACK   ((uint16_t)0x0000)

/* Compact 5x7 uppercase + digit + symbol bitmap font (ASCII 32..95) */
static const uint8_t font5x7[64][5] = {
	{0x00,0x00,0x00,0x00,0x00}, /* ' ' */
	{0x00,0x00,0x5F,0x00,0x00}, /* '!' */
	{0x00,0x07,0x00,0x07,0x00}, /* '"' */
	{0x14,0x7F,0x14,0x7F,0x14}, /* '#' */
	{0x24,0x2A,0x7F,0x2A,0x12}, /* '$' */
	{0x23,0x13,0x08,0x64,0x62}, /* '%' */
	{0x36,0x49,0x55,0x22,0x50}, /* '&' */
	{0x00,0x05,0x03,0x00,0x00}, /* ''' */
	{0x00,0x1C,0x22,0x41,0x00}, /* '(' */
	{0x00,0x41,0x22,0x1C,0x00}, /* ')' */
	{0x14,0x08,0x3E,0x08,0x14}, /* '*' */
	{0x08,0x08,0x3E,0x08,0x08}, /* '+' */
	{0x00,0x50,0x30,0x00,0x00}, /* ',' */
	{0x08,0x08,0x08,0x08,0x08}, /* '-' */
	{0x00,0x60,0x60,0x00,0x00}, /* '.' */
	{0x20,0x10,0x08,0x04,0x02}, /* '/' */
	{0x3E,0x51,0x49,0x45,0x3E}, /* '0' */
	{0x00,0x42,0x7F,0x40,0x00}, /* '1' */
	{0x42,0x61,0x51,0x49,0x46}, /* '2' */
	{0x21,0x41,0x45,0x4B,0x31}, /* '3' */
	{0x18,0x14,0x12,0x7F,0x10}, /* '4' */
	{0x27,0x45,0x45,0x45,0x39}, /* '5' */
	{0x3C,0x4A,0x49,0x49,0x30}, /* '6' */
	{0x01,0x71,0x09,0x05,0x03}, /* '7' */
	{0x36,0x49,0x49,0x49,0x36}, /* '8' */
	{0x06,0x49,0x49,0x29,0x1E}, /* '9' */
	{0x00,0x36,0x36,0x00,0x00}, /* ':' */
	{0x00,0x56,0x36,0x00,0x00}, /* ';' */
	{0x08,0x14,0x22,0x41,0x00}, /* '<' */
	{0x14,0x14,0x14,0x14,0x14}, /* '=' */
	{0x00,0x41,0x22,0x14,0x08}, /* '>' */
	{0x02,0x01,0x51,0x09,0x06}, /* '?' */
	{0x32,0x49,0x79,0x41,0x3E}, /* '@' */
	{0x7E,0x11,0x11,0x11,0x7E}, /* 'A' */
	{0x7F,0x49,0x49,0x49,0x36}, /* 'B' */
	{0x3E,0x41,0x41,0x41,0x22}, /* 'C' */
	{0x7F,0x41,0x41,0x22,0x1C}, /* 'D' */
	{0x7F,0x49,0x49,0x49,0x41}, /* 'E' */
	{0x7F,0x09,0x09,0x09,0x01}, /* 'F' */
	{0x3E,0x41,0x49,0x49,0x7A}, /* 'G' */
	{0x7F,0x08,0x08,0x08,0x7F}, /* 'H' */
	{0x00,0x41,0x7F,0x41,0x00}, /* 'I' */
	{0x20,0x40,0x41,0x3F,0x01}, /* 'J' */
	{0x7F,0x08,0x14,0x22,0x41}, /* 'K' */
	{0x7F,0x40,0x40,0x40,0x40}, /* 'L' */
	{0x7F,0x02,0x0C,0x02,0x7F}, /* 'M' */
	{0x7F,0x04,0x08,0x10,0x7F}, /* 'N' */
	{0x3E,0x41,0x41,0x41,0x3E}, /* 'O' */
	{0x7F,0x09,0x09,0x09,0x06}, /* 'P' */
	{0x3E,0x41,0x51,0x21,0x5E}, /* 'Q' */
	{0x7F,0x09,0x19,0x29,0x46}, /* 'R' */
	{0x46,0x49,0x49,0x49,0x31}, /* 'S' */
	{0x01,0x01,0x7F,0x01,0x01}, /* 'T' */
	{0x3F,0x40,0x40,0x40,0x3F}, /* 'U' */
	{0x1F,0x20,0x40,0x20,0x1F}, /* 'V' */
	{0x3F,0x40,0x38,0x40,0x3F}, /* 'W' */
	{0x63,0x14,0x08,0x14,0x63}, /* 'X' */
	{0x07,0x08,0x70,0x08,0x07}, /* 'Y' */
	{0x61,0x51,0x49,0x45,0x43}, /* 'Z' */
	{0x00,0x7F,0x41,0x41,0x00}, /* '[' */
	{0x02,0x04,0x08,0x10,0x20}, /* '\' */
	{0x00,0x41,0x41,0x7F,0x00}, /* ']' */
	{0x04,0x02,0x01,0x02,0x04}, /* '^' */
	{0x40,0x40,0x40,0x40,0x40}, /* '_' */
};

static inline uint32_t read_cycle32(void) {
	uint32_t c;
	__asm__ volatile("csrr %0, cycle" : "=r"(c));
	return c;
}

static void fill_rect(int x, int y, int w, int h, uint16_t color) {
	volatile uint16_t *fb = bsp_vram_page(0);
	for (int j = 0; j < h; ++j) {
		int py = y + j;
		if (py < 0 || py >= SCREEN_HEIGHT) continue;
		for (int i = 0; i < w; ++i) {
			int px = x + i;
			if (px >= 0 && px < SCREEN_WIDTH) {
				fb[py * SCREEN_WIDTH + px] = color;
			}
		}
	}
}

static void draw_char(int x, int y, char c, uint16_t color) {
	if (c >= 'a' && c <= 'z') {
		c = (char)(c - 'a' + 'A');
	}
	if (c < ' ' || c > '_') {
		c = ' ';
	}
	const uint8_t *glyph = font5x7[c - ' '];
	volatile uint16_t *fb = bsp_vram_page(0);
	for (int col = 0; col < 5; ++col) {
		uint8_t bits = glyph[col];
		int px = x + col;
		if (px < 0 || px >= SCREEN_WIDTH) continue;
		for (int row = 0; row < 7; ++row) {
			if (bits & (1U << row)) {
				int py = y + row;
				if (py >= 0 && py < SCREEN_HEIGHT) {
					fb[py * SCREEN_WIDTH + px] = color;
				}
			}
		}
	}
}

static void draw_str(int x, int y, const char *s, uint16_t color) {
	while (*s) {
		draw_char(x, y, *s++, color);
		x += 6;
	}
}

static void fmt_uint(char *buf, uint32_t v) {
	char tmp[12];
	int i = 0;
	if (v == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}
	while (v > 0) {
		tmp[i++] = (char)('0' + (v % 10U));
		v /= 10U;
	}
	int j = 0;
	while (i > 0) {
		buf[j++] = tmp[--i];
	}
	buf[j] = '\0';
}

static void uart_print_dec(uint32_t v) {
	char buf[12];
	fmt_uint(buf, v);
	bsp_puts(buf);
}

static void draw_tile(int x, int y, int w, int h, uint16_t bg, const char *label) {
	fill_rect(x, y, w, h, C_BORDER);
	fill_rect(x + 1, y + 1, w - 2, h - 2, bg);
	int len = 0;
	while (label[len]) len++;
	int tx = x + (w - len * 6) / 2;
	int ty = y + (h - 7) / 2;
	draw_str(tx, ty, label, (bg == C_PENDING) ? C_GRAY : C_WHITE);
}

static void get_tile_rect(suite_id_t suite, int idx_in_suite,
                          int *x, int *y, int *w, int *h) {
	if (suite == SUITE_UI) {
		int col = idx_in_suite % 10;
		int row = idx_in_suite / 10;
		*w = 28;
		*h = 14;
		*x = 10 + col * 30;
		*y = 32 + row * 17;
	} else if (suite == SUITE_UM) {
		*w = 36;
		*h = 14;
		*x = 10 + idx_in_suite * 38;
		*y = 114;
	} else {
		*w = 28;
		*h = 14;
		*x = 10 + idx_in_suite * 30;
		*y = 144;
	}
}

static void update_status_bar(uint32_t pass_cnt, uint32_t fail_cnt,
                              uint32_t total, uint32_t cycles, int done) {
	uint16_t bar_bg = C_HEADER;
	if (done) {
		bar_bg = (fail_cnt == 0) ? C_PASS : C_FAIL;
	}
	fill_rect(0, 172, SCREEN_WIDTH, 28, bar_bg);

	char line[64];
	char b1[12], b2[12], b3[12], b4[12];
	fmt_uint(b1, pass_cnt);
	fmt_uint(b2, total);
	fmt_uint(b3, fail_cnt);
	fmt_uint(b4, cycles);

	int p = 0;
	const char *s = done ? "DONE  PASS:" : "RUN   PASS:";
	while (*s) line[p++] = *s++;
	for (int i = 0; b1[i]; ++i) line[p++] = b1[i];
	line[p++] = '/';
	for (int i = 0; b2[i]; ++i) line[p++] = b2[i];
	s = "  FAIL:";
	while (*s) line[p++] = *s++;
	for (int i = 0; b3[i]; ++i) line[p++] = b3[i];
	s = "  CYC:";
	while (*s) line[p++] = *s++;
	for (int i = 0; b4[i]; ++i) line[p++] = b4[i];
	line[p] = '\0';

	draw_str(10, 176, line, C_WHITE);
	if (done) {
		draw_str(10, 188, "PRESS ENTER OR ESC TO RETURN TO WOZMON", C_WHITE);
	}
}

int main(void) {
	bsp_set_vsync(0);
	bsp_set_page(0);

	fill_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C_BG);
	fill_rect(0, 0, SCREEN_WIDTH, 18, C_HEADER);
	draw_str(10, 6, "RISC-V OFFICIAL COMPLIANCE (RISCV-TESTS)", C_WHITE);

	draw_str(10, 22, "RV32UI BASE INTEGER", C_CYAN);
	draw_str(10, 104, "RV32UM MULTIPLY / DIVIDE", C_CYAN);
	draw_str(10, 134, "RV32MI MACHINE-MODE TRAPS & CSR", C_CYAN);

	int suite_idx[3] = {0, 0, 0};
	for (int i = 0; i < COMPLIANCE_TEST_COUNT; ++i) {
		suite_id_t s = compliance_tests[i].suite;
		int x, y, w, h;
		get_tile_rect(s, suite_idx[s]++, &x, &y, &w, &h);
		draw_tile(x, y, w, h, C_PENDING, compliance_tests[i].short_name);
	}

	bsp_puts("\n====================================================\n");
	bsp_puts(" RISC-V Official Compliance Suite (riscv-tests)\n");
	bsp_puts(" Target: RV32IM_Zicsr_Zicntr (M-Mode)\n");
	bsp_puts("====================================================\n");

	uint32_t pass_cnt = 0;
	uint32_t fail_cnt = 0;
	uint32_t total_cycles = 0;
	suite_idx[0] = suite_idx[1] = suite_idx[2] = 0;

	for (int i = 0; i < COMPLIANCE_TEST_COUNT; ++i) {
		const compliance_test_t *t = &compliance_tests[i];
		int x, y, w, h;
		get_tile_rect(t->suite, suite_idx[t->suite]++, &x, &y, &w, &h);
		draw_tile(x, y, w, h, C_RUNNING, t->short_name);

		bsp_puts("  [");
		bsp_puts(t->suite_name);
		bsp_puts("] ");
		bsp_puts(t->name);
		bsp_puts(" ... ");

		uint32_t c0 = read_cycle32();
		uint32_t rc = t->fn();
		uint32_t c1 = read_cycle32();
		uint32_t dt = c1 - c0;
		total_cycles += dt;

		if (rc == 0) {
			pass_cnt++;
			draw_tile(x, y, w, h, C_PASS, t->short_name);
			bsp_puts("PASS (");
			uart_print_dec(dt);
			bsp_puts(" cyc)\n");
		} else {
			fail_cnt++;
			draw_tile(x, y, w, h, C_FAIL, t->short_name);
			bsp_puts("FAIL (case #");
			uart_print_dec(rc);
			bsp_puts(")\n");
		}

		update_status_bar(pass_cnt, fail_cnt, COMPLIANCE_TEST_COUNT, total_cycles, 0);
	}

	update_status_bar(pass_cnt, fail_cnt, COMPLIANCE_TEST_COUNT, total_cycles, 1);

	bsp_puts("----------------------------------------------------\n");
	bsp_puts("=== COMPLIANCE DONE: ");
	uart_print_dec(pass_cnt);
	bsp_putc('/');
	uart_print_dec(COMPLIANCE_TEST_COUNT);
	bsp_puts(" PASSED ===\n");
	bsp_puts("Press Enter or Esc to return to Wozmon...\n");

	/* Drain any stale bytes left in UART RX FIFO (e.g., trailing CR from Wozmon) */
	while (bsp_key_avail()) {
		(void)bsp_getc();
	}

	/* Keep visual dashboard visible until user explicitly presses Enter, Esc, or Q */
	for (;;) {
		char c = bsp_getc();
		if (c == '\r' || c == '\n' || c == 27 || c == 'q' || c == 'Q') {
			break;
		}
	}
	return 0;
}
