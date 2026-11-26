/* ============================================================================
 * RV32IM CLOCK FREQUENCY & INSTRUCTIONS-PER-SECOND (IPS) METER
 * Measures exact CPU clock frequency (Hz / MHz) and instructions retired rate
 * (IPS / MIPS, IPC, CPI) using CLINT 1 MHz time/mtime and cycle/instret CSRs.
 * Also supports an on-demand 60-frame VGA VBlank cross-clock check (clk_vga).
 *
 * Controls (UART):
 *   [m] Toggle workload mode: BENCH (ALU+MUL mix) / POLL (CSR poll loop)
 *   [w] Cycle gate window: 10 ms / 100 ms / 1.0 s / 5.0 s
 *   [v] Run 60-frame (~1.0 s) independent VGA VBlank cross-clock measurement
 *   [r] Reset statistics (samples, min/max)
 *   [q] Exit to bootloader
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
#define C_MAGENTA MAKE_RGB(28, 18, 31)

#define BOOT_PROBE_US 10000U /* Fast 10 ms warmup sample on startup */

enum {
  MODE_BENCH = 0,
  MODE_POLL = 1,
};

static const uint32_t k_gate_windows_us[] = {10000U, 100000U, 1000000U,
                                             5000000U};
static const char *const k_gate_labels[] = {"10 MS", "100 MS", "1.0 S",
                                            "5.0 S"};
#define NUM_WINDOWS 4
#define DEFAULT_WIN_IDX 2 /* 1.0 s */

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

typedef struct {
  uint64_t dt_us;
  uint64_t d_cycles;
  uint64_t d_instret;
  uint64_t clk_hz;
  uint64_t ips;
  uint32_t cpi_x1000;
  uint32_t ipc_x1000;
} freq_sample_t;

typedef struct {
  uint32_t samples;
  uint64_t min_hz;
  uint64_t max_hz;
  uint64_t min_ips;
  uint64_t max_ips;
  uint64_t vga_hz;
  uint64_t vga_dt_us;
  int has_vga_ref;
} freq_stats_t;

static volatile uint32_t g_bench_sink = 0;

#ifdef TARGET_MULTI_CYCLE
static inline uint64_t read_csr_cycle(void) {
  uint32_t hi0, lo, hi1;
  do {
    __asm__ volatile("rdcycleh %0" : "=r"(hi0));
    __asm__ volatile("rdcycle  %0" : "=r"(lo));
    __asm__ volatile("rdcycleh %0" : "=r"(hi1));
  } while (hi0 != hi1);
  return ((uint64_t)hi0 << 32) | (uint64_t)lo;
}

static inline uint64_t read_csr_instret(void) {
  uint32_t hi0, lo, hi1;
  do {
    __asm__ volatile("rdinstreth %0" : "=r"(hi0));
    __asm__ volatile("rdinstret  %0" : "=r"(lo));
    __asm__ volatile("rdinstreth %0" : "=r"(hi1));
  } while (hi0 != hi1);
  return ((uint64_t)hi0 << 32) | (uint64_t)lo;
}

static inline uint64_t read_csr_time(void) {
  uint32_t hi0, lo, hi1;
  do {
    __asm__ volatile("rdtimeh %0" : "=r"(hi0));
    __asm__ volatile("rdtime  %0" : "=r"(lo));
    __asm__ volatile("rdtimeh %0" : "=r"(hi1));
  } while (hi0 != hi1);
  return ((uint64_t)hi0 << 32) | (uint64_t)lo;
}

/* Measure over an edge-aligned CLINT time CSR window for sub-10-cycle accuracy */
static void measure_window(uint32_t window_us, int mode, freq_sample_t *out) {
  uint32_t start_lo;
  uint64_t t0, t1, target, coarse_target;
  uint64_t c0, c1, i0, i1;
  uint32_t acc = g_bench_sink ^ 0x13579BDFU;

  /* Align start immediately after a 1 MHz time tick transition */
  __asm__ volatile("rdtime %0" : "=r"(start_lo));
  do {
    t0 = read_csr_time();
  } while ((uint32_t)t0 == start_lo);

  c0 = read_csr_cycle();
  i0 = read_csr_instret();

  target = t0 + (uint64_t)window_us;

  if (mode == MODE_BENCH && window_us > 200U) {
    /* Run computational workload for ~99.9%+ of window, then finish on tight
     * edge poll so start/stop timing jitter cancels out identically. */
    coarse_target = target - 100ULL;
    do {
      for (int k = 0; k < 16; k++) {
        acc = acc * 1664525U + 1013904223U;
        acc ^= (acc >> 13);
        acc += (acc << 5);
        if (acc & 1U) {
          acc ^= 0xA5A55A5AU;
        }
      }
      t1 = read_csr_time();
    } while (t1 < coarse_target);
  }

  do {
    t1 = read_csr_time();
  } while (t1 < target);

  c1 = read_csr_cycle();
  i1 = read_csr_instret();

  g_bench_sink = acc;

  uint64_t dt = (t1 > t0) ? (t1 - t0) : 1ULL;
  uint64_t dc = c1 - c0;
  uint64_t di = i1 - i0;

  out->dt_us = dt;
  out->d_cycles = dc;
  out->d_instret = di;
  out->clk_hz = (dc * 1000000ULL + (dt >> 1)) / dt;
  out->ips = (di * 1000000ULL + (dt >> 1)) / dt;
  out->cpi_x1000 =
      (di > 0ULL) ? (uint32_t)((dc * 1000ULL + (di >> 1)) / di) : 0U;
  out->ipc_x1000 =
      (dc > 0ULL) ? (uint32_t)((di * 1000ULL + (dc >> 1)) / dc) : 0U;
}

/* Cross-check CPU clock against the independent 60 Hz clk_vga VBlank signal.
 * VESA 1280x800@60 nominal pixel clock = 83.46 MHz / (1680 * 828) = 59.99827 Hz
 * -> 60 frames = 1,000,029 us nominal. */
static void measure_vga_vblank_ref(uint32_t frames, uint64_t *out_hz,
                                   uint64_t *out_dt_us, uint64_t *out_cycles) {
  /* Wait for a clean rising edge of vblank */
  while (bsp_vblank())
    ;
  while (!bsp_vblank())
    ;

  uint64_t t0 = read_csr_time();
  uint64_t c0 = read_csr_cycle();

  for (uint32_t f = 0; f < frames; f++) {
    while (bsp_vblank())
      ;
    while (!bsp_vblank())
      ;
  }

  uint64_t c1 = read_csr_cycle();
  uint64_t t1 = read_csr_time();

  uint64_t dc = c1 - c0;
  uint64_t dt = t1 - t0;
  /* Scale dc by (83,460,000 / (1680 * 828 * frames)) = dc * 59.99827 / frames */
  uint64_t hz_est = (dc * 83460000ULL) / (1391040ULL * (uint64_t)frames);

  *out_hz = hz_est;
  *out_dt_us = dt;
  *out_cycles = dc;
}
#endif

/* String & number formatting helpers */
static void u64_to_commas(uint64_t v, char *out) {
  char rev[32];
  int n = 0;
  int digits = 0;

  if (v == 0ULL) {
    out[0] = '0';
    out[1] = '\0';
    return;
  }
  while (v > 0ULL) {
    if (digits > 0 && (digits % 3) == 0) {
      rev[n++] = ',';
    }
    rev[n++] = (char)('0' + (v % 10ULL));
    v /= 10ULL;
    digits++;
  }
  for (int i = 0; i < n; i++) {
    out[i] = rev[n - 1 - i];
  }
  out[n] = '\0';
}

static void u64_to_dec_raw(uint64_t v, char *out) {
  char rev[24];
  int n = 0;
  if (v == 0ULL) {
    out[0] = '0';
    out[1] = '\0';
    return;
  }
  while (v > 0ULL) {
    rev[n++] = (char)('0' + (v % 10ULL));
    v /= 10ULL;
  }
  for (int i = 0; i < n; i++) {
    out[i] = rev[n - 1 - i];
  }
  out[n] = '\0';
}

static void u32_to_dec(uint32_t v, char *out) { u64_to_dec_raw((uint64_t)v, out); }

static void format_milli(uint64_t milli, char *out) {
  uint32_t whole = (uint32_t)(milli / 1000ULL);
  uint32_t frac = (uint32_t)(milli % 1000ULL);
  char wbuf[16];
  u32_to_dec(whole, wbuf);
  int i = 0;
  while (wbuf[i]) {
    out[i] = wbuf[i];
    i++;
  }
  out[i++] = '.';
  out[i++] = (char)('0' + (frac / 100U));
  out[i++] = (char)('0' + ((frac / 10U) % 10U));
  out[i++] = (char)('0' + (frac % 10U));
  out[i] = '\0';
}

static void format_mega(uint64_t hz_or_ips, char *out) {
  /* Convert Hz -> MHz or IPS -> MIPS rounded to 3 decimals */
  uint64_t milli = (hz_or_ips + 500ULL) / 1000ULL;
  format_milli(milli, out);
}

/* VGA drawing primitives */
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

static void render_frame(int page, const freq_sample_t *s,
                         const freq_stats_t *st, int mode, int win_idx) {
  char buf[32];

  fill_rect(page, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C_BG);

  /* Header */
  fill_rect(page, 0, 0, SCREEN_WIDTH, 18, C_HDR);
  draw_str(page, 8, 5, "RV32IM CLOCK + IPS FREQUENCY METER", C_WHITE, 1);

  /* Panel 1: CPU Clock Frequency */
  fill_rect(page, 10, 22, 300, 48, C_PANEL);
  draw_rect_outline(page, 10, 22, 300, 48, C_CYAN);
  draw_str(page, 18, 27, "CPU CLOCK FREQUENCY (MCYCLE / TIME)", C_CYAN, 1);

  format_mega(s->clk_hz, buf);
  draw_str(page, 18, 38, buf, C_GREEN, 2);
  draw_str(page, 134, 44, "MHZ", C_GRAY, 1);

  u64_to_commas(s->clk_hz, buf);
  draw_str(page, 174, 44, buf, C_WHITE, 1);
  draw_str(page, 274, 44, "HZ", C_GRAY, 1);

  /* Panel 2: Instructions Retired Frequency */
  fill_rect(page, 10, 75, 300, 48, C_PANEL);
  draw_rect_outline(page, 10, 75, 300, 48, C_AMBER);
  draw_str(page, 18, 80, "INSTRUCTIONS RETIRED (INSTRET / TIME)", C_AMBER, 1);

  format_mega(s->ips, buf);
  draw_str(page, 18, 91, buf, C_AMBER, 2);
  draw_str(page, 134, 97, "MIPS", C_GRAY, 1);

  u64_to_commas(s->ips, buf);
  draw_str(page, 174, 97, buf, C_WHITE, 1);
  draw_str(page, 274, 97, "IPS", C_GRAY, 1);

  /* Panel 3: IPC, CPI, Gate, Mode, Min/Max */
  fill_rect(page, 10, 128, 300, 52, C_PANEL);
  draw_rect_outline(page, 10, 128, 300, 52, C_BORDER);

  draw_str(page, 18, 134, "IPC:", C_GRAY, 1);
  format_milli(s->ipc_x1000, buf);
  draw_str(page, 46, 134, buf, C_CYAN, 1);

  draw_str(page, 94, 134, "CPI:", C_GRAY, 1);
  format_milli(s->cpi_x1000, buf);
  draw_str(page, 122, 134, buf, C_WHITE, 1);

  draw_str(page, 170, 134, "MODE:", C_GRAY, 1);
  draw_str(page, 204, 134, (mode == MODE_BENCH) ? "BENCH" : "POLL", C_GREEN,
           1);

  draw_str(page, 250, 134, "WIN:", C_GRAY, 1);
  draw_str(page, 274, 134, k_gate_labels[win_idx], C_WHITE, 1);

  draw_str(page, 18, 146, "CLK MIN/MAX:", C_GRAY, 1);
  format_mega(st->min_hz, buf);
  draw_str(page, 96, 146, buf, C_WHITE, 1);
  draw_str(page, 152, 146, "/", C_GRAY, 1);
  format_mega(st->max_hz, buf);
  draw_str(page, 162, 146, buf, C_WHITE, 1);
  draw_str(page, 220, 146, "N=", C_GRAY, 1);
  u32_to_dec(st->samples, buf);
  draw_str(page, 234, 146, buf, C_CYAN, 1);

  if (st->has_vga_ref) {
    draw_str(page, 18, 160, "VGA-REF(60F):", C_MAGENTA, 1);
    u64_to_commas(st->vga_hz, buf);
    draw_str(page, 102, 160, buf, C_WHITE, 1);
    draw_str(page, 204, 160, "HZ", C_GRAY, 1);
  } else {
    draw_str(page, 18, 160, "GATE US:", C_GRAY, 1);
    u64_to_commas(s->dt_us, buf);
    draw_str(page, 72, 160, buf, C_WHITE, 1);
    draw_str(page, 154, 160, "CYC:", C_GRAY, 1);
    u64_to_commas(s->d_cycles, buf);
    draw_str(page, 182, 160, buf, C_WHITE, 1);
  }

  /* Footer */
  draw_str(page, 8, 186, "[M] MODE [W] GATE [V] VGA-REF [R] RST [Q] EXIT",
           C_GRAY, 1);
}

static void print_sample_uart(uint32_t seq, const freq_sample_t *s, int mode,
                              int is_probe) {
  char buf[32];

  bsp_puts(is_probe ? "[PROBE] #" : "[FREQ]  #");
  u32_to_dec(seq, buf);
  bsp_puts(buf);
  bsp_puts((mode == MODE_BENCH) ? " [BENCH] dt=" : " [POLL]  dt=");
  u64_to_dec_raw(s->dt_us, buf);
  bsp_puts(buf);
  bsp_puts(" us | CLK=");
  u64_to_commas(s->clk_hz, buf);
  bsp_puts(buf);
  bsp_puts(" Hz (");
  format_mega(s->clk_hz, buf);
  bsp_puts(buf);
  bsp_puts(" MHz) | RET=");
  u64_to_commas(s->ips, buf);
  bsp_puts(buf);
  bsp_puts(" IPS (");
  format_mega(s->ips, buf);
  bsp_puts(buf);
  bsp_puts(" MIPS) | IPC=");
  format_milli(s->ipc_x1000, buf);
  bsp_puts(buf);
  bsp_puts(" | CPI=");
  format_milli(s->cpi_x1000, buf);
  bsp_puts(buf);
  bsp_puts("\n");
}

static void update_stats(freq_stats_t *st, const freq_sample_t *s) {
  st->samples++;
  if (st->samples == 1U) {
    st->min_hz = s->clk_hz;
    st->max_hz = s->clk_hz;
    st->min_ips = s->ips;
    st->max_ips = s->ips;
  } else {
    if (s->clk_hz < st->min_hz)
      st->min_hz = s->clk_hz;
    if (s->clk_hz > st->max_hz)
      st->max_hz = s->clk_hz;
    if (s->ips < st->min_ips)
      st->min_ips = s->ips;
    if (s->ips > st->max_ips)
      st->max_ips = s->ips;
  }
}

int main(void) {
  bsp_puts("\n====================================================\n");
  bsp_puts(" RV32IM Clock Frequency & Instruction Rate Meter\n");
  bsp_puts(" Controls: [m] Mode  [w] Window  [v] VGA-Ref  [r] Reset  [q] Exit\n");
  bsp_puts("====================================================\n");

#ifndef TARGET_MULTI_CYCLE
  bsp_puts("[ERROR] CLINT timer and cycle/instret CSRs require multi_cycle.\n");
  bsp_exit();
  return 0;
#else
  int mode = MODE_BENCH;
  int win_idx = DEFAULT_WIN_IDX;
  int page = 0;
  freq_sample_t sample;
  freq_stats_t stats = {0};

  /* Verify MMIO mtime vs rdtime CSR coherence */
  uint64_t mmio_t = bsp_time_us();
  uint64_t csr_t = read_csr_time();
  uint64_t delta = (csr_t >= mmio_t) ? (csr_t - mmio_t) : (mmio_t - csr_t);
  char dbuf[24];
  bsp_puts("[CHECK] mtime MMIO vs rdtime CSR delta=");
  u64_to_dec_raw(delta, dbuf);
  bsp_puts(dbuf);
  bsp_puts(" us\n");

  /* Quick 10 ms startup probe so both simulators and humans see immediate data */
  measure_window(BOOT_PROBE_US, MODE_POLL, &sample);
  print_sample_uart(0U, &sample, MODE_POLL, 1);
  stats.min_hz = sample.clk_hz;
  stats.max_hz = sample.clk_hz;
  stats.min_ips = sample.ips;
  stats.max_ips = sample.ips;
  render_frame(page, &sample, &stats, MODE_POLL, 0);
  bsp_present_page(page);

  while (1) {
    char key;
    while ((key = bsp_try_getc()) != 0) {
      if (key == 'q' || key == 'Q' || key == 27) {
        bsp_puts("[FREQ] Exiting to bootloader...\n");
        bsp_exit();
      } else if (key == 'm' || key == 'M') {
        mode = (mode == MODE_BENCH) ? MODE_POLL : MODE_BENCH;
        bsp_puts(mode == MODE_BENCH ? "[CTRL] Mode = BENCH (ALU+MUL mix)\n"
                                    : "[CTRL] Mode = POLL (tight CSR poll)\n");
      } else if (key == 'w' || key == 'W') {
        win_idx = (win_idx + 1) % NUM_WINDOWS;
        bsp_puts("[CTRL] Gate window = ");
        bsp_puts(k_gate_labels[win_idx]);
        bsp_puts("\n");
      } else if (key == 'r' || key == 'R') {
        stats.samples = 0;
        stats.has_vga_ref = 0;
        bsp_puts("[CTRL] Statistics reset.\n");
      } else if (key == 'v' || key == 'V') {
        uint64_t vga_hz, vga_dt, vga_cyc;
        char b1[32], b2[32], b3[32];
        bsp_puts("[VGA-REF] Measuring 60 VBlank frames (clk_vga=83.46 MHz)...\n");
        measure_vga_vblank_ref(60U, &vga_hz, &vga_dt, &vga_cyc);
        stats.vga_hz = vga_hz;
        stats.vga_dt_us = vga_dt;
        stats.has_vga_ref = 1;
        u64_to_commas(vga_cyc, b1);
        u64_to_dec_raw(vga_dt, b2);
        u64_to_commas(vga_hz, b3);
        bsp_puts("[VGA-REF] 60 frames: cycles=");
        bsp_puts(b1);
        bsp_puts(" | clint_dt=");
        bsp_puts(b2);
        bsp_puts(" us | est_clk=");
        bsp_puts(b3);
        bsp_puts(" Hz (");
        format_mega(vga_hz, b1);
        bsp_puts(b1);
        bsp_puts(" MHz)\n");
      }
    }

    measure_window(k_gate_windows_us[win_idx], mode, &sample);
    update_stats(&stats, &sample);
    print_sample_uart(stats.samples, &sample, mode, 0);

    int back = 1 - page;
    render_frame(back, &sample, &stats, mode, win_idx);
    bsp_present_page(back);
    page = back;
  }
#endif
}
