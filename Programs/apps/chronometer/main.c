/* ============================================================================
 * RV32IM CHRONOMETER / STOPWATCH & TIMER VERIFICATION APP
 * Tests 1 MHz CLINT mtime/mtimecmp, 100 Hz MTI interrupts, and time/timeh CSRs
 * VGA: 320x200 RGB565 double-buffered display
 * UART controls: Space/s = Start/Pause, l = Lap, r = Reset, q/Esc = Exit
 * ============================================================================
 */

#include "bsp.h"
#include <stdint.h>

#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define C_BG      MAKE_RGB(1, 3, 6)
#define C_HDR     MAKE_RGB(3, 8, 16)
#define C_PANEL   MAKE_RGB(2, 5, 10)
#define C_BORDER  MAKE_RGB(8, 18, 12)
#define C_WHITE   MAKE_RGB(31, 63, 31)
#define C_GRAY    MAKE_RGB(20, 42, 20)
#define C_CYAN    MAKE_RGB(0, 63, 31)
#define C_GREEN   MAKE_RGB(4, 63, 10)
#define C_AMBER   MAKE_RGB(31, 46, 0)
#define C_RED     MAKE_RGB(31, 10, 6)

#define IRQ_PERIOD_US 10000ULL /* 10 ms -> 100 Hz Machine Timer Interrupt */
#define MAX_LAPS      4

/* 5x7 uppercase bitmap font (ASCII 32..95) */
static const uint8_t font5x7[64][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, /* ' ' */
    {0x00, 0x00, 0x5F, 0x00, 0x00}, /* '!' */
    {0x00, 0x07, 0x00, 0x07, 0x00}, /* '"' */
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, /* '#' */
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, /* '$' */
    {0x23, 0x13, 0x08, 0x64, 0x62}, /* '%' */
    {0x36, 0x49, 0x55, 0x22, 0x50}, /* '&' */
    {0x00, 0x05, 0x03, 0x00, 0x00}, /* ''' */
    {0x00, 0x1C, 0x22, 0x41, 0x00}, /* '(' */
    {0x00, 0x41, 0x22, 0x1C, 0x00}, /* ')' */
    {0x14, 0x08, 0x3E, 0x08, 0x14}, /* '*' */
    {0x08, 0x08, 0x3E, 0x08, 0x08}, /* '+' */
    {0x00, 0x50, 0x30, 0x00, 0x00}, /* ',' */
    {0x08, 0x08, 0x08, 0x08, 0x08}, /* '-' */
    {0x00, 0x60, 0x60, 0x00, 0x00}, /* '.' */
    {0x20, 0x10, 0x08, 0x04, 0x02}, /* '/' */
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, /* '0' */
    {0x00, 0x42, 0x7F, 0x40, 0x00}, /* '1' */
    {0x42, 0x61, 0x51, 0x49, 0x46}, /* '2' */
    {0x21, 0x41, 0x45, 0x4B, 0x31}, /* '3' */
    {0x18, 0x14, 0x12, 0x7F, 0x10}, /* '4' */
    {0x27, 0x45, 0x45, 0x45, 0x39}, /* '5' */
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, /* '6' */
    {0x01, 0x71, 0x09, 0x05, 0x03}, /* '7' */
    {0x36, 0x49, 0x49, 0x49, 0x36}, /* '8' */
    {0x06, 0x49, 0x49, 0x29, 0x1E}, /* '9' */
    {0x00, 0x36, 0x36, 0x00, 0x00}, /* ':' */
    {0x00, 0x56, 0x36, 0x00, 0x00}, /* ';' */
    {0x08, 0x14, 0x22, 0x41, 0x00}, /* '<' */
    {0x14, 0x14, 0x14, 0x14, 0x14}, /* '=' */
    {0x00, 0x41, 0x22, 0x14, 0x08}, /* '>' */
    {0x02, 0x01, 0x51, 0x09, 0x06}, /* '?' */
    {0x32, 0x49, 0x79, 0x41, 0x3E}, /* '@' */
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, /* 'A' */
    {0x7F, 0x49, 0x49, 0x49, 0x36}, /* 'B' */
    {0x3E, 0x41, 0x41, 0x41, 0x22}, /* 'C' */
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, /* 'D' */
    {0x7F, 0x49, 0x49, 0x49, 0x41}, /* 'E' */
    {0x7F, 0x09, 0x09, 0x09, 0x01}, /* 'F' */
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, /* 'G' */
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, /* 'H' */
    {0x00, 0x41, 0x7F, 0x41, 0x00}, /* 'I' */
    {0x20, 0x40, 0x41, 0x3F, 0x01}, /* 'J' */
    {0x7F, 0x08, 0x14, 0x22, 0x41}, /* 'K' */
    {0x7F, 0x40, 0x40, 0x40, 0x40}, /* 'L' */
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, /* 'M' */
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, /* 'N' */
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, /* 'O' */
    {0x7F, 0x09, 0x09, 0x09, 0x06}, /* 'P' */
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, /* 'Q' */
    {0x7F, 0x09, 0x19, 0x29, 0x46}, /* 'R' */
    {0x46, 0x49, 0x49, 0x49, 0x31}, /* 'S' */
    {0x01, 0x01, 0x7F, 0x01, 0x01}, /* 'T' */
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, /* 'U' */
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, /* 'V' */
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, /* 'W' */
    {0x63, 0x14, 0x08, 0x14, 0x63}, /* 'X' */
    {0x07, 0x08, 0x70, 0x08, 0x07}, /* 'Y' */
    {0x61, 0x51, 0x49, 0x45, 0x43}, /* 'Z' */
    {0x00, 0x7F, 0x41, 0x41, 0x00}, /* '[' */
    {0x02, 0x04, 0x08, 0x10, 0x20}, /* '\' */
    {0x00, 0x41, 0x41, 0x7F, 0x00}, /* ']' */
    {0x04, 0x02, 0x01, 0x02, 0x04}, /* '^' */
    {0x40, 0x40, 0x40, 0x40, 0x40}, /* '_' */
};

static volatile uint32_t g_irq_ticks = 0;
static volatile uint32_t g_chrono_cs = 0; /* Elapsed centiseconds (10 ms) */
static volatile uint32_t g_running = 1;
static volatile uint64_t g_next_cmp = 0;

#ifdef TARGET_MULTI_CYCLE
static uint64_t read_csr_time(void) {
  uint32_t hi0, lo, hi1;
  do {
    __asm__ volatile("csrr %0, timeh" : "=r"(hi0));
    __asm__ volatile("csrr %0, time" : "=r"(lo));
    __asm__ volatile("csrr %0, timeh" : "=r"(hi1));
  } while (hi0 != hi1);
  return ((uint64_t)hi0 << 32) | (uint64_t)lo;
}

__attribute__((interrupt("machine"), aligned(4))) static void
chrono_trap_handler(void) {
  uint32_t mcause;
  __asm__ volatile("csrr %0, mcause" : "=r"(mcause));

  if (mcause == 0x80000007UL) {
    uint64_t now;
    uint32_t hi0, lo, hi1;
    do {
      hi0 = *BSP_MTIME_HI;
      lo = *BSP_MTIME_LO;
      hi1 = *BSP_MTIME_HI;
    } while (hi0 != hi1);
    now = ((uint64_t)hi0 << 32) | (uint64_t)lo;

    g_irq_ticks++;
    if (g_running) {
      g_chrono_cs++;
    }

    g_next_cmp += IRQ_PERIOD_US;
    if (g_next_cmp <= now) {
      g_next_cmp = now + IRQ_PERIOD_US;
    }

    *BSP_MTIMECMP_LO = 0xFFFFFFFFU;
    *BSP_MTIMECMP_HI = (uint32_t)(g_next_cmp >> 32);
    *BSP_MTIMECMP_LO = (uint32_t)(g_next_cmp & 0xFFFFFFFFU);
  }
}

static void timer_irq_init(void) {
  __asm__ volatile("csrci mstatus, 8" ::: "memory");
  g_next_cmp = bsp_time_us() + IRQ_PERIOD_US;
  bsp_timer_set_cmp(g_next_cmp);
  __asm__ volatile("csrw mtvec, %0" :: "r"(chrono_trap_handler));
  __asm__ volatile("csrw mie, %0" :: "r"(1U << 7)); /* MTIE */
  __asm__ volatile("csrsi mstatus, 8" ::: "memory"); /* MIE */
}
#endif

static void uart_put_u32(uint32_t v) {
  char buf[11];
  int idx = 10;
  buf[idx] = '\0';
  if (v == 0) {
    bsp_putc('0');
    return;
  }
  while (v > 0 && idx > 0) {
    buf[--idx] = (char)('0' + (v % 10U));
    v /= 10U;
  }
  bsp_puts(&buf[idx]);
}

static void format_cs(uint32_t cs, char *out) {
  uint32_t cc = cs % 100U;
  uint32_t total_s = cs / 100U;
  uint32_t ss = total_s % 60U;
  uint32_t mm = (total_s / 60U) % 100U;
  out[0] = (char)('0' + (mm / 10U));
  out[1] = (char)('0' + (mm % 10U));
  out[2] = ':';
  out[3] = (char)('0' + (ss / 10U));
  out[4] = (char)('0' + (ss % 10U));
  out[5] = '.';
  out[6] = (char)('0' + (cc / 10U));
  out[7] = (char)('0' + (cc % 10U));
  out[8] = '\0';
}

static void u32_to_dec(uint32_t v, char *out) {
  char tmp[11];
  int n = 0;
  if (v == 0) {
    out[0] = '0';
    out[1] = '\0';
    return;
  }
  while (v > 0) {
    tmp[n++] = (char)('0' + (v % 10U));
    v /= 10U;
  }
  for (int i = 0; i < n; i++) {
    out[i] = tmp[n - 1 - i];
  }
  out[n] = '\0';
}

static void fill_rect(int page, int x, int y, int w, int h, uint16_t color) {
  volatile uint16_t *vram = bsp_vram_page(page);
  if (x < 0) {
    w += x;
    x = 0;
  }
  if (y < 0) {
    h += y;
    y = 0;
  }
  if (x + w > SCREEN_WIDTH)
    w = SCREEN_WIDTH - x;
  if (y + h > SCREEN_HEIGHT)
    h = SCREEN_HEIGHT - y;
  if (w <= 0 || h <= 0)
    return;

  for (int dy = 0; dy < h; dy++) {
    uint32_t row = (uint32_t)(y + dy) * SCREEN_WIDTH + (uint32_t)x;
    for (int dx = 0; dx < w; dx++) {
      vram[row + (uint32_t)dx] = color;
    }
  }
}

static void draw_rect_outline(int page, int x, int y, int w, int h,
                              uint16_t color) {
  fill_rect(page, x, y, w, 1, color);
  fill_rect(page, x, y + h - 1, w, 1, color);
  fill_rect(page, x, y, 1, h, color);
  fill_rect(page, x + w - 1, y, 1, h, color);
}

static void draw_char_scaled(int page, int x, int y, char c, uint16_t fg,
                             int scale) {
  if (c >= 'a' && c <= 'z')
    c = (char)(c - 'a' + 'A');
  if (c < 32 || c > 95)
    c = ' ';
  const uint8_t *glyph = font5x7[(int)c - 32];
  volatile uint16_t *vram = bsp_vram_page(page);

  for (int col = 0; col < 5; col++) {
    uint8_t bits = glyph[col];
    for (int row = 0; row < 7; row++) {
      if (!(bits & (1U << row)))
        continue;
      int px0 = x + col * scale;
      int py0 = y + row * scale;
      for (int sy = 0; sy < scale; sy++) {
        int py = py0 + sy;
        if (py < 0 || py >= SCREEN_HEIGHT)
          continue;
        uint32_t base = (uint32_t)py * SCREEN_WIDTH;
        for (int sx = 0; sx < scale; sx++) {
          int px = px0 + sx;
          if (px >= 0 && px < SCREEN_WIDTH) {
            vram[base + (uint32_t)px] = fg;
          }
        }
      }
    }
  }
}

static void draw_str(int page, int x, int y, const char *s, uint16_t fg,
                     int scale) {
  int step = 6 * scale;
  while (*s) {
    draw_char_scaled(page, x, y, *s++, fg, scale);
    x += step;
  }
}

static void render_frame(int page, uint32_t cs, uint32_t irqs, uint64_t elapsed_us,
                         uint32_t running, const uint32_t *laps,
                         int lap_count) {
  char tbuf[12];
  char nbuf[16];

  fill_rect(page, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C_BG);

  /* Header */
  fill_rect(page, 0, 0, SCREEN_WIDTH, 18, C_HDR);
  draw_str(page, 8, 5, "CHRONOMETER  CLINT 1MHZ + MTI 100HZ", C_WHITE, 1);

  /* Main clock panel */
  fill_rect(page, 16, 24, 288, 66, C_PANEL);
  draw_rect_outline(page, 16, 24, 288, 66, running ? C_CYAN : C_AMBER);

  format_cs(cs, tbuf);
  /* 8 chars * 24 px = 192 px -> centered at x = (320 - 192) / 2 = 64 */
  draw_str(page, 64, 34, tbuf, running ? C_GREEN : C_AMBER, 4);

  draw_str(page, 26, 74, running ? "[RUNNING]" : "[PAUSED] ",
           running ? C_GREEN : C_AMBER, 1);

  draw_str(page, 108, 74, "MTI:", C_GRAY, 1);
  u32_to_dec(irqs, nbuf);
  draw_str(page, 136, 74, nbuf, C_CYAN, 1);

  /* Elapsed hardware mtime panel */
  fill_rect(page, 16, 96, 288, 22, C_PANEL);
  draw_rect_outline(page, 16, 96, 288, 22, C_BORDER);
  draw_str(page, 24, 103, "MTIME MS:", C_GRAY, 1);
  u32_to_dec((uint32_t)(elapsed_us / 1000ULL), nbuf);
  draw_str(page, 84, 103, nbuf, C_WHITE, 1);
  draw_str(page, 166, 103, "MM:SS.CC", C_GRAY, 1);

  /* Laps panel */
  fill_rect(page, 16, 124, 288, 52, C_PANEL);
  draw_rect_outline(page, 16, 124, 288, 52, C_BORDER);
  draw_str(page, 24, 129, "LAPS", C_CYAN, 1);
  if (lap_count == 0) {
    draw_str(page, 24, 144, "PRESS [L] TO RECORD A LAP", C_GRAY, 1);
  } else {
    uint32_t prev = 0;
    for (int i = 0; i < lap_count; i++) {
      char lstr[12];
      char sstr[12];
      int y = 139 + i * 9;
      draw_str(page, 24, y, "L", C_GRAY, 1);
      nbuf[0] = (char)('1' + i);
      nbuf[1] = ':';
      nbuf[2] = '\0';
      draw_str(page, 30, y, nbuf, C_GRAY, 1);
      format_cs(laps[i], lstr);
      draw_str(page, 48, y, lstr, C_WHITE, 1);
      format_cs(laps[i] - prev, sstr);
      draw_str(page, 120, y, "+", C_CYAN, 1);
      draw_str(page, 126, y, sstr, C_CYAN, 1);
      prev = laps[i];
    }
  }

  /* Footer controls */
  draw_str(page, 16, 184, "[SPC/S] RUN  [L] LAP  [R] RST  [Q] EXIT", C_GRAY,
           1);
}

int main(void) {
  uint32_t laps[MAX_LAPS];
  int lap_count = 0;
  uint32_t last_printed_sec = 0xFFFFFFFFU;
  uint32_t last_drawn_cs = 0xFFFFFFFFU;
  uint32_t last_drawn_run = 0xFFFFFFFFU;
  int last_drawn_laps = -1;
  int page = 0;
  char tbuf[12];

  bsp_puts("\n====================================================\n");
  bsp_puts(" Chronometer (CLINT 1 MHz mtime + 100 Hz MTI Test)\n");
  bsp_puts(" Controls: [Space/s] Start/Pause  [l] Lap  [r] Reset  [q] Exit\n");
  bsp_puts("====================================================\n");

#ifdef TARGET_MULTI_CYCLE
  uint64_t mmio_t = bsp_time_us();
  uint64_t csr_t = read_csr_time();
  uint32_t csr_delta = (uint32_t)((csr_t >= mmio_t) ? (csr_t - mmio_t)
                                                    : (mmio_t - csr_t));
  bsp_puts("[CHECK] mtime MMIO vs rdtime CSR delta=");
  uart_put_u32(csr_delta);
  bsp_puts(" us\n");

  timer_irq_init();
#else
  bsp_puts("[NOTE] Running without multi_cycle CLINT/MTI hardware.\n");
#endif

  uint64_t start_us = bsp_time_us();
  render_frame(0, 0, 0, 0ULL, g_running, laps, lap_count);
  bsp_present_page(0);

  while (1) {
    char key = bsp_try_getc();
    if (key == 'q' || key == 'Q' || key == 27) {
      bsp_puts("[CHRONO] Exiting to bootloader...\n");
      break;
    } else if (key == ' ' || key == 's' || key == 'S') {
      g_running = !g_running;
      format_cs(g_chrono_cs, tbuf);
      bsp_puts(g_running ? "[CHRONO] RESUMED at " : "[CHRONO] PAUSED at ");
      bsp_puts(tbuf);
      bsp_puts("\n");
      last_drawn_run = 0xFFFFFFFFU;
    } else if (key == 'r' || key == 'R') {
      g_chrono_cs = 0;
      g_irq_ticks = 0;
      start_us = bsp_time_us();
      lap_count = 0;
      last_printed_sec = 0xFFFFFFFFU;
      last_drawn_cs = 0xFFFFFFFFU;
      bsp_puts("[CHRONO] RESET to 00:00.00\n");
    } else if (key == 'l' || key == 'L') {
      uint32_t snap = g_chrono_cs;
      if (lap_count < MAX_LAPS) {
        laps[lap_count++] = snap;
      } else {
        for (int i = 1; i < MAX_LAPS; i++)
          laps[i - 1] = laps[i];
        laps[MAX_LAPS - 1] = snap;
      }
      format_cs(snap, tbuf);
      bsp_puts("[CHRONO] LAP: ");
      bsp_puts(tbuf);
      bsp_puts(" | mti_irqs=");
      uart_put_u32(g_irq_ticks);
      bsp_puts("\n");
      last_drawn_laps = -1;
    }

    uint32_t cur_cs = g_chrono_cs;
    uint32_t cur_run = g_running;
    uint32_t cur_irqs = g_irq_ticks;
    uint64_t now_us = bsp_time_us();
    uint64_t elapsed_us = now_us - start_us;
    uint32_t cur_sec = cur_cs / 100U;

    if (cur_sec != last_printed_sec && (cur_run || last_printed_sec == 0xFFFFFFFFU)) {
      last_printed_sec = cur_sec;
      format_cs(cur_cs, tbuf);
      bsp_puts("[CHRONO] ");
      bsp_puts(tbuf);
      bsp_puts(" | dt_us=");
      uart_put_u32((uint32_t)elapsed_us);
      bsp_puts(" | mti_irqs=");
      uart_put_u32(cur_irqs);
      bsp_puts(cur_run ? " | RUN\n" : " | PAUSE\n");
    }

    if (cur_cs != last_drawn_cs || cur_run != last_drawn_run ||
        lap_count != last_drawn_laps) {
      int back = 1 - page;
      render_frame(back, cur_cs, cur_irqs, elapsed_us, cur_run, laps,
                   lap_count);
      bsp_present_page(back);
      page = back;
      last_drawn_cs = cur_cs;
      last_drawn_run = cur_run;
      last_drawn_laps = lap_count;
    }
  }

  bsp_exit();
  return 0;
}
