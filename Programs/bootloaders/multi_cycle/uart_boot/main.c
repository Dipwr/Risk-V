#include <stdint.h>

#define UART_DATA ((volatile uint32_t *)0x20000000U)
#define UART_STAT ((volatile uint32_t *)0x20000004U)
#define PAGE_REG  ((volatile uint32_t *)0x20000008U)
#define VRAM_P0   ((volatile uint16_t *)0x10000000U)

#define SCREEN_W 320
#define SCREEN_H 200

#define USER_RAM_BASE 0x00002000U
#define USER_RAM_END  0x00040000U

#define UART_RX_READY (1U << 0)
#define UART_TX_READY (1U << 1)
#define UART_RX_OVR   (1U << 2)
#define UART_RX_FRM   (1U << 3)
#define UART_TX_IDLE  (1U << 4)
#define UART_RX_FLUSH (1U << 4)

#define PROTO_ACK 0x06U
#define PROTO_NAK 0x15U

#define C_BG      ((uint16_t)0x0842)
#define C_HEADER  ((uint16_t)0x10A6)
#define C_BORDER  ((uint16_t)0x4228)
#define C_BAR_BG  ((uint16_t)0x18C3)
#define C_BAR_FG  ((uint16_t)0x05E0)
#define C_WHITE   ((uint16_t)0xFFFF)
#define C_CYAN    ((uint16_t)0x5FFF)
#define C_YELLOW  ((uint16_t)0xFFE0)
#define C_GREEN   ((uint16_t)0x07E0)
#define C_RED     ((uint16_t)0xF800)

#define BAR_X       20
#define BAR_Y       120
#define BAR_W       280
#define BAR_H       16
#define BAR_INNER_X (BAR_X + 2)
#define BAR_INNER_Y (BAR_Y + 2)
#define BAR_INNER_W (BAR_W - 4)
#define BAR_INNER_H (BAR_H - 4)

/* Compact 5x7 font (ASCII 32..95) */
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

/* Nibble lookup table for IEEE 802.3 CRC32 (poly 0xEDB88320) */
static const uint32_t crc32_nibble[16] = {
	0x00000000U, 0x1DB71064U, 0x3B6E20C8U, 0x26D930ACU,
	0x76DC4190U, 0x6B6B51F4U, 0x4DB26158U, 0x5005713CU,
	0xEDB88320U, 0xF00F9344U, 0xD6D6A3E8U, 0xCB61B38CU,
	0x9B64C2B0U, 0x86D3D2D4U, 0xA00AE278U, 0xBDBDF21CU,
};

static inline uint32_t crc32_step(uint32_t crc, uint8_t b) {
	crc ^= b;
	crc = (crc >> 4) ^ crc32_nibble[crc & 0x0FU];
	crc = (crc >> 4) ^ crc32_nibble[crc & 0x0FU];
	return crc;
}

static void uart_putc(uint8_t c) {
	while (!(*UART_STAT & UART_TX_READY)) {
	}
	*UART_DATA = (uint32_t)c;
}

static void uart_puts(const char *s) {
	while (*s) {
		uart_putc((uint8_t)*s++);
	}
}

static uint8_t uart_getc(void) {
	while (!(*UART_STAT & UART_RX_READY)) {
	}
	return (uint8_t)(*UART_DATA & 0xFFU);
}

static uint32_t uart_read_u32(void) {
	uint32_t b0 = uart_getc();
	uint32_t b1 = uart_getc();
	uint32_t b2 = uart_getc();
	uint32_t b3 = uart_getc();
	return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

static void uart_wait_tx_idle(void) {
	while (!(*UART_STAT & UART_TX_IDLE)) {
	}
}

static void uart_flush_rx(void) {
	*UART_STAT = UART_RX_OVR | UART_RX_FRM | UART_RX_FLUSH;
}

static void fill_rect(int x, int y, int w, int h, uint16_t color) {
	for (int j = 0; j < h; ++j) {
		int py = y + j;
		if (py < 0 || py >= SCREEN_H) {
			continue;
		}
		volatile uint16_t *row = &VRAM_P0[py * SCREEN_W];
		for (int i = 0; i < w; ++i) {
			int px = x + i;
			if (px >= 0 && px < SCREEN_W) {
				row[px] = color;
			}
		}
	}
}

static void draw_char(int x, int y, char c, uint16_t fg) {
	if (c >= 'a' && c <= 'z') {
		c = (char)(c - 'a' + 'A');
	}
	if (c < ' ' || c > '_') {
		c = ' ';
	}
	const uint8_t *glyph = font5x7[c - ' '];
	for (int col = 0; col < 5; ++col) {
		uint8_t bits = glyph[col];
		int px = x + col;
		if (px < 0 || px >= SCREEN_W) {
			continue;
		}
		for (int row = 0; row < 7; ++row) {
			if (bits & (1U << row)) {
				int py = y + row;
				if (py >= 0 && py < SCREEN_H) {
					VRAM_P0[py * SCREEN_W + px] = fg;
				}
			}
		}
	}
}

static void draw_str(int x, int y, const char *s, uint16_t fg) {
	while (*s) {
		draw_char(x, y, *s++, fg);
		x += 6;
	}
}

static void set_status(const char *msg, uint16_t color) {
	fill_rect(10, 92, 300, 14, C_BG);
	draw_str(20, 95, msg, color);
}

static void reset_progress_bar(void) {
	fill_rect(BAR_X, BAR_Y, BAR_W, BAR_H, C_BORDER);
	fill_rect(BAR_INNER_X, BAR_INNER_Y, BAR_INNER_W, BAR_INNER_H, C_BAR_BG);
}

static void draw_boot_screen(void) {
	fill_rect(0, 0, SCREEN_W, SCREEN_H, C_BG);
	fill_rect(0, 0, SCREEN_W, 22, C_HEADER);
	draw_str(12, 7, "RISK-V UART BOOTLOADER", C_WHITE);
	draw_str(20, 40, "115200 8N1  USER RAM: 0X00002000 (248KB)", C_CYAN);
	draw_str(20, 56, "PROTOCOL: RVBL / RVGO + CRC32", C_WHITE);
	set_status("READY - WAITING FOR UPLOAD", C_YELLOW);
	reset_progress_bar();
}

static void jump_to(uint32_t addr) {
	uart_wait_tx_idle();
	void (*entry)(void) = (void (*)(void))addr;
	entry();
}

void boot_main(void) {
	*PAGE_REG = 0U;
	uart_flush_rx();
	draw_boot_screen();
	uart_puts("RVBL READY\r\n");

	uint32_t magic = 0;
	for (;;) {
		uint8_t b = uart_getc();
		magic = (magic << 8) | (uint32_t)b;

		if (magic == 0x5256424CU) { /* "RVBL" */
			magic = 0;
			uint32_t load_addr    = uart_read_u32();
			uint32_t size         = uart_read_u32();
			uint32_t expected_crc = uart_read_u32();

			if (load_addr < USER_RAM_BASE || load_addr >= USER_RAM_END ||
			    (load_addr & 3U) != 0U || size == 0U ||
			    size > (USER_RAM_END - load_addr)) {
				uart_putc(PROTO_NAK);
				uart_putc('B');
				set_status("ERROR: BAD HEADER", C_RED);
				uart_flush_rx();
				continue;
			}

			*UART_STAT = UART_RX_OVR | UART_RX_FRM;
			uart_putc(PROTO_ACK);
			set_status("RECEIVING BINARY...", C_CYAN);
			reset_progress_bar();

			volatile uint8_t *dst = (volatile uint8_t *)load_addr;
			uint32_t crc = 0xFFFFFFFFU;
			uint32_t prev_col = 0;

			for (uint32_t i = 0; i < size; ++i) {
				uint8_t rx_byte = uart_getc();
				dst[i] = rx_byte;
				crc = crc32_step(crc, rx_byte);

				uint32_t col = ((i + 1U) * (uint32_t)BAR_INNER_W) / size;
				if (col > prev_col) {
					fill_rect(BAR_INNER_X + (int)prev_col, BAR_INNER_Y,
					          (int)(col - prev_col), BAR_INNER_H, C_BAR_FG);
					prev_col = col;
				}
			}
			crc ^= 0xFFFFFFFFU;

			uint32_t stat = *UART_STAT;
			if (stat & (UART_RX_OVR | UART_RX_FRM)) {
				uart_putc(PROTO_NAK);
				uart_putc('U');
				set_status("ERROR: UART OVERRUN/FRAMING", C_RED);
				uart_flush_rx();
				continue;
			}

			if (crc != expected_crc) {
				uart_putc(PROTO_NAK);
				uart_putc('C');
				set_status("ERROR: CRC32 MISMATCH", C_RED);
				uart_flush_rx();
				continue;
			}

			uart_putc(PROTO_ACK);
			set_status("CRC OK - BOOTING...", C_GREEN);
			jump_to(load_addr);
		} else if (magic == 0x5256474FU) { /* "RVGO" */
			magic = 0;
			uint32_t entry_addr = uart_read_u32();
			if (entry_addr < USER_RAM_BASE || entry_addr >= USER_RAM_END ||
			    (entry_addr & 3U) != 0U) {
				uart_putc(PROTO_NAK);
				uart_putc('B');
				set_status("ERROR: BAD JUMP ADDR", C_RED);
				uart_flush_rx();
				continue;
			}
			uart_putc(PROTO_ACK);
			set_status("BOOTING PRELOADED IMAGE...", C_GREEN);
			jump_to(entry_addr);
		}
	}
}
