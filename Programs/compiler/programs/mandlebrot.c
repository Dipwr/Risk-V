#include <stdint.h>

// Hardware MMIO Base Addresses
#define GRAPHIC_RAM ((volatile uint32_t *)0x00082000)
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

// Resolution Specs
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define MAX_ITER 20

// Q6.10 Fixed-Point Format (1.0 = 1024)
#define FIXED_SHIFT 10
#define FIXED_ONE (1 << FIXED_SHIFT)

// Pre-computed 16-bit RGB 5-5-5 Palette LUT
static uint16_t palette_lut[MAX_ITER + 1];

// ----------------------------------------------------
// Bare-Metal RV32I Software Runtime Routines
// ----------------------------------------------------

int __mulsi3(int a, int b) {
  int res = 0;
  int neg = (a < 0) ^ (b < 0);
  unsigned int ua = (a < 0) ? -a : a;
  unsigned int ub = (b < 0) ? -b : b;
  while (ub > 0) {
    if (ub & 1)
      res += ua;
    ua <<= 1;
    ub >>= 1;
  }
  return neg ? -res : res;
}

int __divsi3(int a, int b) {
  if (b == 0)
    return 0;

  int neg = (a < 0) ^ (b < 0);
  unsigned int num = (a < 0) ? -a : a;
  unsigned int den = (b < 0) ? -b : b;

  unsigned int quot = 0;
  unsigned int rem = 0;

  for (int i = 31; i >= 0; i--) {
    rem = (rem << 1) | ((num >> i) & 1);
    if (rem >= den) {
      rem -= den;
      quot |= (1U << i);
    }
  }

  return neg ? -(int)quot : (int)quot;
}

static inline int fix_mul(int a, int b) {
  return __mulsi3(a, b) >> FIXED_SHIFT;
}

// ----------------------------------------------------
// Palette Generation (Non-Saturating Color Gradient)
// ----------------------------------------------------

void init_palette(void) {
  for (int i = 0; i < MAX_ITER; i++) {
    uint32_t r, g, b;

    if (i < 16) {
      // Phase 1: Deep Blue -> Cyan (i: 0..15)
      r = 0;
      g = (i * 31) / 15;
      b = 31 - (i * 15) / 15;
    } else if (i < 32) {
      // Phase 2: Cyan -> Warm Orange (i: 16..31)
      int idx = i - 16;
      r = (idx * 31) / 15;
      g = 31 - (idx * 16) / 15;
      b = 0;
    } else {
      // Phase 3: Orange -> Deep Violet (i: 32..47)
      int idx = i - 32;
      r = 31 - (idx * 16) / 15;
      g = 0;
      b = (idx * 28) / 15;
    }

    palette_lut[i] = 0x8000 | (r << 10) | (g << 5) | b;
  }
  // Solid Black for interior points
  palette_lut[MAX_ITER] = 0x8000;
}

// Main Cardioid & Period-2 Bulb Early Rejection
static inline int in_mandelbrot_interior(int x0, int y0) {
  int x_sub = x0 - (FIXED_ONE >> 2);
  int y2 = fix_mul(y0, y0);
  int q = fix_mul(x_sub, x_sub) + y2;

  int lhs = fix_mul(q, q + x_sub);
  int rhs = y2 >> 2;

  if (lhs < rhs)
    return 1;

  int x_add = x0 + FIXED_ONE;
  if ((fix_mul(x_add, x_add) + y2) < (FIXED_ONE >> 4))
    return 1;

  return 0;
}

// Evaluate a single point in the complex plane
static inline uint16_t sample_mandelbrot(int x0, int y0) {
  if (in_mandelbrot_interior(x0, y0)) {
    return palette_lut[MAX_ITER];
  }

  int zr = 0;
  int zi = 0;
  int iter = 0;
  int escape_bound = 4 * FIXED_ONE;

  while (iter < MAX_ITER) {
    int zr2 = fix_mul(zr, zr);
    int zi2 = fix_mul(zi, zi);

    if ((zr2 + zi2) > escape_bound)
      break;

    int two_zr_zi = fix_mul(zr, zi) << 1;
    zr = zr2 - zi2 + x0;
    zi = two_zr_zi + y0;
    iter++;
  }

  return palette_lut[iter];
}

// Render loop with 2x2 SSAA
void render_mandelbrot(int page, int center_x, int center_y, int scale) {
  int page_offset = page * BUFFER_SIZE;
  int half_w = SCREEN_WIDTH / 2;
  int half_h = SCREEN_HEIGHT / 2;

  // Sub-pixel offsets (+/- 0.25 of a pixel step)
  int quarter_step = scale >> 2;

  for (int py = 0; py < SCREEN_HEIGHT; py++) {
    int y0 = center_y + __mulsi3(py - half_h, scale);
    int row_offset = page_offset + (py * SCREEN_WIDTH);

    for (int px = 0; px < SCREEN_WIDTH; px++) {
      int x0 = center_x + __mulsi3(px - half_w, scale);

      // --- 2x2 Super-Sampling (4 sub-pixel samples) ---
      uint16_t c0 = sample_mandelbrot(x0 - quarter_step, y0 - quarter_step);
      uint16_t c1 = sample_mandelbrot(x0 + quarter_step, y0 - quarter_step);
      uint16_t c2 = sample_mandelbrot(x0 - quarter_step, y0 + quarter_step);
      uint16_t c3 = sample_mandelbrot(x0 + quarter_step, y0 + quarter_step);

      // Extract and sum RGB 5-bit color channels
      uint32_t r = ((c0 >> 10) & 0x1F) + ((c1 >> 10) & 0x1F) +
                   ((c2 >> 10) & 0x1F) + ((c3 >> 10) & 0x1F);
      uint32_t g = ((c0 >> 5) & 0x1F) + ((c1 >> 5) & 0x1F) +
                   ((c2 >> 5) & 0x1F) + ((c3 >> 5) & 0x1F);
      uint32_t b = (c0 & 0x1F) + (c1 & 0x1F) + (c2 & 0x1F) + (c3 & 0x1F);

      // Average colors (divide by 4 via >> 2) and pack back to RGB 5-5-5 format
      GRAPHIC_RAM[row_offset + px] =
          0x8000 | ((r >> 2) << 10) | ((g >> 2) << 5) | (b >> 2);
    }
  }
}

int main(void) {
  init_palette();

  uint32_t active_page = 0;

  int center_x = -768; // -0.75 in Q6.10
  int center_y = 0;
  int scale = 10; // Step size per pixel

  int needs_redraw = 1;

  while (1) {
    if (needs_redraw) {
      uint32_t back_page = active_page ^ 1;

      render_mandelbrot(back_page, center_x, center_y, scale);

      active_page = back_page;
      *PAGE_REG = active_page;
      needs_redraw = 0;
    }

    if (*KEY_STAT & 0x1) {
      uint8_t key = (uint8_t)(*KEY_DATA & 0xFF);

      if (key == 'w' || key == 'W') {
        center_y -= (scale * 15);
        needs_redraw = 1;
      } else if (key == 's' || key == 'S') {
        center_y += (scale * 15);
        needs_redraw = 1;
      } else if (key == 'a' || key == 'A') {
        center_x -= (scale * 15);
        needs_redraw = 1;
      } else if (key == 'd' || key == 'D') {
        center_x += (scale * 15);
        needs_redraw = 1;
      } else if (key == 'i' || key == 'I' || key == '+') {
        scale = (scale * 3) >> 2;
        needs_redraw = 1;
      } else if (key == 'o' || key == 'O' || key == '-') {
        scale = (scale * 5) >> 2;
        needs_redraw = 1;
      } else if (key == 'r' || key == 'R') {
        center_x = -768;
        center_y = 0;
        scale = 10;
        needs_redraw = 1;
      } else if (key == 'q' || key == 'Q' || key == 27) {
        break;
      }
    }
  }

  *PAGE_REG = 0;
  return 0;
}