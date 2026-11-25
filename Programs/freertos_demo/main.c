#include "bsp.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include <stdint.h>
#include <stdio.h>

extern void freertos_risc_v_trap_handler(void);

/* Override weak symbol in FreeRTOS RISC-V port.c (no CLINT/timer IRQ) */
void vPortSetupTimerInterrupt(void) {
}

void freertos_unhandled_irq(void) {
	bsp_puts("[RTOS] Unexpected interrupt/exception!\n");
	bsp_exit();
}

typedef struct {
	uint64_t cycles;
	uint64_t instret;
	uint32_t anim_frames;
	uint32_t yield_count;
} telemetry_msg_t;

static QueueHandle_t g_telemetry_q = NULL;
static volatile uint32_t g_anim_frames = 0;
static volatile uint32_t g_yield_count = 0;
static volatile uint32_t g_msg_rx_count = 0;

/* 5x7 uppercase/digit/symbol font (ASCII 32..95) */
static const uint8_t font5x7[64][5] = {
	{0x00,0x00,0x00,0x00,0x00}, {0x00,0x00,0x5F,0x00,0x00},
	{0x00,0x07,0x00,0x07,0x00}, {0x14,0x7F,0x14,0x7F,0x14},
	{0x24,0x2A,0x7F,0x2A,0x12}, {0x23,0x13,0x08,0x64,0x62},
	{0x36,0x49,0x55,0x22,0x50}, {0x00,0x05,0x03,0x00,0x00},
	{0x00,0x1C,0x22,0x41,0x00}, {0x00,0x41,0x22,0x1C,0x00},
	{0x14,0x08,0x3E,0x08,0x14}, {0x08,0x08,0x3E,0x08,0x08},
	{0x00,0x50,0x30,0x00,0x00}, {0x08,0x08,0x08,0x08,0x08},
	{0x00,0x60,0x60,0x00,0x00}, {0x20,0x10,0x08,0x04,0x02},
	{0x3E,0x51,0x49,0x45,0x3E}, {0x00,0x42,0x7F,0x40,0x00},
	{0x42,0x61,0x51,0x49,0x46}, {0x21,0x41,0x45,0x4B,0x31},
	{0x18,0x14,0x12,0x7F,0x10}, {0x27,0x45,0x45,0x45,0x39},
	{0x3C,0x4A,0x49,0x49,0x30}, {0x01,0x71,0x09,0x05,0x03},
	{0x36,0x49,0x49,0x49,0x36}, {0x06,0x49,0x49,0x29,0x1E},
	{0x00,0x36,0x36,0x00,0x00}, {0x00,0x56,0x36,0x00,0x00},
	{0x08,0x14,0x22,0x41,0x00}, {0x14,0x14,0x14,0x14,0x14},
	{0x00,0x41,0x22,0x14,0x08}, {0x02,0x01,0x51,0x09,0x06},
	{0x32,0x49,0x79,0x41,0x3E}, {0x7E,0x11,0x11,0x11,0x7E},
	{0x7F,0x49,0x49,0x49,0x36}, {0x3E,0x41,0x41,0x41,0x22},
	{0x7F,0x41,0x41,0x22,0x1C}, {0x7F,0x49,0x49,0x49,0x41},
	{0x7F,0x09,0x09,0x09,0x01}, {0x3E,0x41,0x49,0x49,0x7A},
	{0x7F,0x08,0x08,0x08,0x7F}, {0x00,0x41,0x7F,0x41,0x00},
	{0x20,0x40,0x41,0x3F,0x01}, {0x7F,0x08,0x14,0x22,0x41},
	{0x7F,0x40,0x40,0x40,0x40}, {0x7F,0x02,0x0C,0x02,0x7F},
	{0x7F,0x04,0x08,0x10,0x7F}, {0x3E,0x41,0x41,0x41,0x3E},
	{0x7F,0x09,0x09,0x09,0x06}, {0x3E,0x41,0x51,0x21,0x5E},
	{0x7F,0x09,0x19,0x29,0x46}, {0x46,0x49,0x49,0x49,0x31},
	{0x01,0x01,0x7F,0x01,0x01}, {0x3F,0x40,0x40,0x40,0x3F},
	{0x1F,0x20,0x40,0x20,0x1F}, {0x3F,0x40,0x38,0x40,0x3F},
	{0x63,0x14,0x08,0x14,0x63}, {0x07,0x08,0x70,0x08,0x07},
	{0x61,0x51,0x49,0x45,0x43}, {0x00,0x7F,0x41,0x41,0x00},
	{0x02,0x04,0x08,0x10,0x20}, {0x00,0x41,0x41,0x7F,0x00},
	{0x04,0x02,0x01,0x02,0x04}, {0x40,0x40,0x40,0x40,0x40},
};

static inline uint64_t read_cycle64(void) {
	uint32_t hi0, lo, hi1;
	do {
		__asm__ volatile("rdcycleh %0" : "=r"(hi0));
		__asm__ volatile("rdcycle  %0" : "=r"(lo));
		__asm__ volatile("rdcycleh %0" : "=r"(hi1));
	} while (hi0 != hi1);
	return ((uint64_t)hi0 << 32) | lo;
}

static inline uint64_t read_instret64(void) {
	uint32_t hi0, lo, hi1;
	do {
		__asm__ volatile("rdinstreth %0" : "=r"(hi0));
		__asm__ volatile("rdinstret  %0" : "=r"(lo));
		__asm__ volatile("rdinstreth %0" : "=r"(hi1));
	} while (hi0 != hi1);
	return ((uint64_t)hi0 << 32) | lo;
}

static void fill_rect(int page, int x, int y, int w, int h, uint16_t color) {
	volatile uint16_t *fb = bsp_vram_page(page);
	for (int j = 0; j < h; ++j) {
		int py = y + j;
		if (py < 0 || py >= SCREEN_HEIGHT) {
			continue;
		}
		volatile uint16_t *row = &fb[py * SCREEN_WIDTH];
		for (int i = 0; i < w; ++i) {
			int px = x + i;
			if (px >= 0 && px < SCREEN_WIDTH) {
				row[px] = color;
			}
		}
	}
}

static void draw_char(int page, int x, int y, char c, uint16_t fg, uint16_t bg) {
	if (c >= 'a' && c <= 'z') {
		c = (char)(c - 'a' + 'A');
	}
	if (c < ' ' || c > '_') {
		c = ' ';
	}
	const uint8_t *glyph = font5x7[c - ' '];
	volatile uint16_t *fb = bsp_vram_page(page);
	for (int col = 0; col < 5; ++col) {
		uint8_t bits = glyph[col];
		int px = x + col;
		if (px < 0 || px >= SCREEN_WIDTH) {
			continue;
		}
		for (int row = 0; row < 7; ++row) {
			int py = y + row;
			if (py >= 0 && py < SCREEN_HEIGHT) {
				fb[py * SCREEN_WIDTH + px] = (bits & (1U << row)) ? fg : bg;
			}
		}
	}
}

static void draw_str(int page, int x, int y, const char *s, uint16_t fg, uint16_t bg) {
	while (*s) {
		draw_char(page, x, y, *s++, fg, bg);
		x += 6;
	}
}

static void vAnimTask(void *pvParameters) {
	(void)pvParameters;
	int bx[4] = {20, 90, 170, 240};
	int vx[4] = {2, -3, 3, -2};
	int prev_bx[2][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}};
	const uint16_t colors[4] = {0xF800, 0x07E0, 0x001F, 0xFFE0};
	int active_page = 0;

	for (;;) {
		int back_page = active_page ^ 1;

		for (int i = 0; i < 4; ++i) {
			int y = 96 + i * 24;
			if (prev_bx[back_page][i] >= 0) {
				fill_rect(back_page, prev_bx[back_page][i], y, 36, 16, 0x0842);
			}
		}

		for (int i = 0; i < 4; ++i) {
			int y = 96 + i * 24;
			fill_rect(back_page, bx[i], y, 36, 16, colors[i]);
			prev_bx[back_page][i] = bx[i];
			bx[i] += vx[i];
			if (bx[i] <= 12) {
				bx[i] = 12;
				vx[i] = -vx[i];
			} else if (bx[i] >= 272) {
				bx[i] = 272;
				vx[i] = -vx[i];
			}
		}

		g_anim_frames++;
		bsp_set_page(back_page);
		while (bsp_active_page() != back_page) {
			taskYIELD();
		}
		active_page = back_page;
	}
}

static void vTelemetryTask(void *pvParameters) {
	(void)pvParameters;
	for (;;) {
		g_yield_count++;
		telemetry_msg_t msg;
		msg.cycles = read_cycle64();
		msg.instret = read_instret64();
		msg.anim_frames = g_anim_frames;
		msg.yield_count = g_yield_count;

		(void)xQueueSend(g_telemetry_q, &msg, 0);
		taskYIELD();
	}
}

static void vConsoleTask(void *pvParameters) {
	(void)pvParameters;
	telemetry_msg_t msg;
	char line[64];
	uint32_t last_vga_frame = 0xFFFFFFFFU;
	uint32_t last_uart_frame = 0xFFFFFFFFU;

	for (;;) {
		if (xQueueReceive(g_telemetry_q, &msg, 0) == pdPASS) {
			g_msg_rx_count++;
			if (msg.anim_frames != last_vga_frame && (msg.anim_frames % 4U) == 0U) {
				last_vga_frame = msg.anim_frames;
				snprintf(line, sizeof(line),
				         "FRAMES:%-6lu YIELDS:%-6lu Q_RX:%-6lu",
				         (unsigned long)msg.anim_frames,
				         (unsigned long)msg.yield_count,
				         (unsigned long)g_msg_rx_count);
				draw_str(0, 12, 32, line, 0xFFFF, 0x0842);
				draw_str(1, 12, 32, line, 0xFFFF, 0x0842);

				snprintf(line, sizeof(line),
				         "CYC:%-10lu INST:%-10lu",
				         (unsigned long)(msg.cycles & 0xFFFFFFFFULL),
				         (unsigned long)(msg.instret & 0xFFFFFFFFULL));
				draw_str(0, 12, 46, line, 0x5FFF, 0x0842);
				draw_str(1, 12, 46, line, 0x5FFF, 0x0842);
			}

			if (msg.anim_frames != last_uart_frame &&
			    (msg.anim_frames == 1U || (msg.anim_frames % 15U) == 0U)) {
				last_uart_frame = msg.anim_frames;
				printf("[RTOS] frame=%lu yield=%lu q_rx=%lu cyc=%lu inst=%lu\n",
				       (unsigned long)msg.anim_frames,
				       (unsigned long)msg.yield_count,
				       (unsigned long)g_msg_rx_count,
				       (unsigned long)(msg.cycles & 0xFFFFFFFFULL),
				       (unsigned long)(msg.instret & 0xFFFFFFFFULL));
			}
		}

		char ch = bsp_try_getc();
		if (ch == 'q' || ch == 'Q' || ch == 27) {
			printf("[RTOS] Exiting to bootloader...\n");
			bsp_exit();
		}

		taskYIELD();
	}
}

int main(void) {
	bsp_set_vsync(1);
	bsp_present_page(0);

	for (int p = 0; p < 2; ++p) {
		fill_rect(p, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x0842);
		fill_rect(p, 0, 0, SCREEN_WIDTH, 20, 0x10A6);
		draw_str(p, 12, 6, "FREERTOS V11.1.0 COOPERATIVE (ECALL/MRET)", 0xFFFF, 0x10A6);
		draw_str(p, 12, 62, "PRESS Q OR ESC TO EXIT TO BOOTLOADER", 0xFFE0, 0x0842);
		fill_rect(p, 8, 86, 304, 110, 0x4228);
		fill_rect(p, 10, 88, 300, 106, 0x0842);
	}

	printf("\n====================================================\n");
	printf(" FreeRTOS Kernel V11.1.0 Cooperative Demo (RV32IM)\n");
	printf(" Press 'q' or ESC to return to bootloader\n");
	printf("====================================================\n");

	/* Install FreeRTOS trap handler into mtvec for ECALL/MRET yields */
	__asm__ volatile("csrw mtvec, %0" :: "r"(freertos_risc_v_trap_handler));

	g_telemetry_q = xQueueCreate(8, sizeof(telemetry_msg_t));
	configASSERT(g_telemetry_q != NULL);

	BaseType_t r1 = xTaskCreate(vAnimTask, "anim", 384, NULL, tskIDLE_PRIORITY + 1, NULL);
	BaseType_t r2 = xTaskCreate(vTelemetryTask, "telem", 384, NULL, tskIDLE_PRIORITY + 1, NULL);
	BaseType_t r3 = xTaskCreate(vConsoleTask, "console", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
	configASSERT(r1 == pdPASS && r2 == pdPASS && r3 == pdPASS);

	vTaskStartScheduler();

	for (;;) {
	}
}
