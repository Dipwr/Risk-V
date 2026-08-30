/* ============================================================================
 * RV32IM BARE-METAL MANDELBROT (COSINE PALETTES + SATELLITE STRUCTURES)
 * ============================================================================
 */

#include <stdint.h>

// Hardware MMIO Base Addresses
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define COLOR_WHITE MAKE_RGB(31, 63, 31)
#define COLOR_CYAN MAKE_RGB(0, 63, 31)
#define COLOR_BLACK MAKE_RGB(0, 0, 0)
#define COLOR_GRAY MAKE_RGB(6, 12, 6)

// ----------------------------------------------------
// MATH ENGINE (Q4.12)
// ----------------------------------------------------
#define FIXED_SHIFT 12
#define FIXED_ONE (1 << FIXED_SHIFT)

static inline int fix_mul(int a, int b) { return (a * b) >> FIXED_SHIFT; }

// Fixed-point sine/cosine helper for palette generation (Input: 0 to 1023 ->
// Output: -256 to 256)
static int integer_cos(int angle_1024) {
  // Simple 4-segment polynomial approximation for 2*PI cycle
  int x = angle_1024 & 1023;
  if (x < 256)
    return 256 - ((x * x) >> 6);
  if (x < 512) {
    int dx = x - 256;
    return -((dx * dx) >> 6);
  }
  if (x < 768) {
    int dx = 512 - x;
    return -((dx * dx) >> 6);
  }
  int dx = 1024 - x;
  return 256 - ((dx * dx) >> 6);
}

// ----------------------------------------------------
// 1024-STEP PALETTE SYSTEM
// ----------------------------------------------------
#define PALETTE_SIZE 1024
static uint16_t palette_lut[PALETTE_SIZE];
static int max_iter = 40;
static int active_palette_type = 0;

void init_palette(void) {
  for (int i = 0; i < PALETTE_SIZE; i++) {
    int r8 = 0, g8 = 0, b8 = 0;

    if (active_palette_type == 0) {
      // PRESET 0: Classic Ultra Fractal (Navy -> Blue -> White -> Gold ->
      // Black)
      int anchors[6][4] = {{0, 0, 7, 100},       {164, 32, 107, 203},
                           {430, 237, 255, 255}, {655, 255, 170, 0},
                           {870, 0, 2, 0},       {1024, 0, 7, 100}};
      int seg = 0;
      while (seg < 5 && i >= anchors[seg + 1][0])
        seg++;
      int range = anchors[seg + 1][0] - anchors[seg][0];
      int offset = i - anchors[seg][0];
      r8 = anchors[seg][1] +
           ((anchors[seg + 1][1] - anchors[seg][1]) * offset) / range;
      g8 = anchors[seg][2] +
           ((anchors[seg + 1][2] - anchors[seg][2]) * offset) / range;
      b8 = anchors[seg][3] +
           ((anchors[seg + 1][3] - anchors[seg][3]) * offset) / range;

    } else if (active_palette_type == 1) {
      // PRESET 1: "Sunset Fire" (Blackish Purple -> Crimson -> Gold -> White)
      // IQ Cosine Parameters: a=(0.5,0.2,0.1), b=(0.5,0.2,0.1),
      // c=(1.0,1.0,1.0), d=(0.0,0.33,0.67)
      r8 = 128 + ((128 * integer_cos(i)) >> 8);
      g8 = 51 + ((51 * integer_cos(i + 341)) >> 8);
      b8 = 25 + ((25 * integer_cos(i + 682)) >> 8);

    } else {
      // PRESET 2: "Spectrum Wave" (High-Contrast Rainbow Cycle)
      // IQ Cosine Parameters: a=(0.5,0.5,0.5), b=(0.5,0.5,0.5),
      // c=(1.0,1.0,1.0), d=(0.0,0.33,0.67)
      r8 = 128 + ((127 * integer_cos(i)) >> 8);
      g8 = 128 + ((127 * integer_cos(i + 341)) >> 8);
      b8 = 128 + ((127 * integer_cos(i + 682)) >> 8);
    }

    // Clamp values
    if (r8 < 0)
      r8 = 0;
    if (r8 > 255)
      r8 = 255;
    if (g8 < 0)
      g8 = 0;
    if (g8 > 255)
      g8 = 255;
    if (b8 < 0)
      b8 = 0;
    if (b8 > 255)
      b8 = 255;

    palette_lut[i] = MAKE_RGB(r8 >> 3, g8 >> 2, b8 >> 3);
  }
}

// ----------------------------------------------------
// EMBEDDED 8x8 VGA FONT & GUI DRAWING ROUTINES
// ----------------------------------------------------
static const uint8_t font8x8_basic[95][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},
    {0x36, 0x36, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00},
    {0x18, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x18, 0x00},
    {0x00, 0x63, 0x66, 0x0C, 0x18, 0x33, 0x63, 0x00},
    {0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00},
    {0x30, 0x30, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00},
    {0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00},
    {0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00},
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},
    {0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30},
    {0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},
    {0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},
    {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00},
    {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00},
    {0x3C, 0x66, 0x06, 0x0C, 0x18, 0x30, 0x7E, 0x00},
    {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00},
    {0x0C, 0x1C, 0x3C, 0x6C, 0xFE, 0x0C, 0x0C, 0x00},
    {0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00},
    {0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00},
    {0x7E, 0x66, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x00},
    {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00},
    {0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00},
    {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00},
    {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 0x00},
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},
    {0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00},
    {0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00},
    {0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00},
    {0x3C, 0x66, 0x6E, 0x6E, 0x60, 0x3E, 0x00, 0x00},
    {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00},
    {0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00},
    {0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00},
    {0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00},
    {0xFE, 0x60, 0x60, 0x7C, 0x60, 0x60, 0xFE, 0x00},
    {0xFE, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00},
    {0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3E, 0x00},
    {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},
    {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // Fixed 'I'
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C, 0x00},
    {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00},
    {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xFE, 0x00},
    {0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x00},
    {0x66, 0x76, 0x7E, 0x6E, 0x66, 0x66, 0x66, 0x00},
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00},
    {0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00},
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x0E, 0x00},
    {0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x00},
    {0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00},
    {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00},
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00},
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00},
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x36, 0x00},
    {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00},
    {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00},
    {0xFE, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFE, 0x00},
    {0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00},
    {0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00},
    {0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00},
    {0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
    {0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00},
    {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x7C, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 0x00},
    {0x06, 0x06, 0x3E, 0x66, 0x66, 0x66, 0x3E, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00},
    {0x1C, 0x30, 0x7C, 0x30, 0x30, 0x30, 0x30, 0x00},
    {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x3C},
    {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00},
    {0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // Fixed 'i'
    {0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x38},
    {0x60, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0x00},
    {0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00},
    {0x00, 0x00, 0x6C, 0xFE, 0xD6, 0xC6, 0xC6, 0x00},
    {0x00, 0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00},
    {0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60},
    {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x06},
    {0x00, 0x00, 0x7C, 0x66, 0x60, 0x60, 0x60, 0x00},
    {0x00, 0x00, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x00},
    {0x18, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x0E, 0x00},
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00},
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00},
    {0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00},
    {0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00},
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x3C},
    {0x00, 0x00, 0x7E, 0x0C, 0x18, 0x30, 0x7E, 0x00},
    {0x0E, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0E, 0x00},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00},
    {0x70, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x70, 0x00},
    {0x3A, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

void draw_filled_rect(int page, int x, int y, int w, int h, uint16_t color) {
  int page_offset = page * PAGE_PIXELS;
  for (int dy = 0; dy < h; dy++) {
    int py = y + dy;
    if (py < 0 || py >= SCREEN_HEIGHT)
      continue;
    int row_offset = page_offset + (py * SCREEN_WIDTH);
    for (int dx = 0; dx < w; dx++) {
      int px = x + dx;
      if (px >= 0 && px < SCREEN_WIDTH) {
        GRAPHIC_RAM[row_offset + px] = color;
      }
    }
  }
}

void draw_char(int page, int x, int y, char c, uint16_t color) {
  if (c < 32 || c > 126)
    return;
  const uint8_t *glyph = font8x8_basic[c - 32];
  int page_offset = page * PAGE_PIXELS;

  for (int row = 0; row < 8; row++) {
    int py = y + row;
    if (py < 0 || py >= SCREEN_HEIGHT)
      continue;
    int row_offset = page_offset + (py * SCREEN_WIDTH);

    for (int col = 0; col < 8; col++) {
      int px = x + col;
      if (px >= 0 && px < SCREEN_WIDTH) {
        if (glyph[row] & (1 << (7 - col))) {
          GRAPHIC_RAM[row_offset + px] = color;
        }
      }
    }
  }
}

void draw_string(int page, int x, int y, const char *str, uint16_t color) {
  int cur_x = x;
  while (*str) {
    draw_char(page, cur_x, y, *str, color);
    cur_x += 8;
    str++;
  }
}

void draw_help_window(int page) {
  int w = 260, h = 160;
  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;

  draw_filled_rect(page, x, y, w, h, COLOR_WHITE);
  draw_filled_rect(page, x + 2, y + 2, w - 4, h - 4, COLOR_GRAY);

  draw_string(page, x + 60, y + 10, "--- CONTROLS ---", COLOR_CYAN);
  draw_string(page, x + 15, y + 30, "W/A/S/D  : Move Camera", COLOR_WHITE);
  draw_string(page, x + 15, y + 45, "I/O      : Zoom In / Out", COLOR_WHITE);
  draw_string(page, x + 15, y + 60, "[ / ]    : Max Iterations", COLOR_WHITE);
  draw_string(page, x + 15, y + 75, "C / V    : Color Density", COLOR_WHITE);
  draw_string(page, x + 15, y + 90, "P        : Switch Palette", COLOR_WHITE);
  draw_string(page, x + 15, y + 105, "T        : Toggle Anti-Alias",
              COLOR_WHITE);
  draw_string(page, x + 15, y + 120, "R        : Reset View", COLOR_WHITE);
  draw_string(page, x + 15, y + 135, "H        : Toggle Help Window",
              COLOR_WHITE);
}

// ----------------------------------------------------
// FRACTAL LOGIC
// ----------------------------------------------------
static inline int in_mandelbrot_interior(int x0, int y0) {
  int x_sub = x0 - (FIXED_ONE >> 2);
  int y2 = fix_mul(y0, y0);
  int q = fix_mul(x_sub, x_sub) + y2;

  if (fix_mul(q, q + x_sub) < (y2 >> 2))
    return 1;
  if ((fix_mul(x0 + FIXED_ONE, x0 + FIXED_ONE) + y2) < (FIXED_ONE >> 4))
    return 1;
  return 0;
}

static inline uint16_t sample_mandelbrot(int x0, int y0, int density) {
  if (in_mandelbrot_interior(x0, y0))
    return 0x0000;

  int zr = 0, zi = 0, iter = 0;
  int escape_bound = 4 * FIXED_ONE;

  while (iter < max_iter) {
    int zr2 = fix_mul(zr, zr);
    int zi2 = fix_mul(zi, zi);

    if ((zr2 + zi2) > escape_bound)
      break;

    int two_zr_zi = (zr * zi) >> (FIXED_SHIFT - 1);
    zr = zr2 - zi2 + x0;
    zi = two_zr_zi + y0;
    iter++;
  }

  if (iter == max_iter)
    return 0x0000;
  return palette_lut[(iter * density) & 1023];
}

// ----------------------------------------------------
// RENDER PIPELINE
// ----------------------------------------------------
void render_mandelbrot(int page, int center_x, int center_y, int scale,
                       int use_ssaa, int density) {
  int page_offset = page * PAGE_PIXELS;
  int half_w = SCREEN_WIDTH / 2;
  int half_h = SCREEN_HEIGHT / 2;

  int quarter_step = scale >> 2;

  int effective_ssaa = use_ssaa;
  if (quarter_step == 0)
    effective_ssaa = 0;

  int x_start = center_x - (half_w * scale);
  int y_start = center_y - (half_h * scale);

  int y0 = y_start;
  for (int py = 0; py < SCREEN_HEIGHT; py++) {
    int row_offset = page_offset + (py * SCREEN_WIDTH);
    int x0 = x_start;

    for (int px = 0; px < SCREEN_WIDTH; px++) {
      if (effective_ssaa) {
        uint16_t c0 =
            sample_mandelbrot(x0 - quarter_step, y0 - quarter_step, density);
        uint16_t c1 =
            sample_mandelbrot(x0 + quarter_step, y0 - quarter_step, density);
        uint16_t c2 =
            sample_mandelbrot(x0 - quarter_step, y0 + quarter_step, density);
        uint16_t c3 =
            sample_mandelbrot(x0 + quarter_step, y0 + quarter_step, density);

        uint32_t r = ((c0 >> 11) & 0x1F) + ((c1 >> 11) & 0x1F) +
                     ((c2 >> 11) & 0x1F) + ((c3 >> 11) & 0x1F);
        uint32_t g = ((c0 >> 5) & 0x3F) + ((c1 >> 5) & 0x3F) +
                     ((c2 >> 5) & 0x3F) + ((c3 >> 5) & 0x3F);
        uint32_t b = (c0 & 0x1F) + (c1 & 0x1F) + (c2 & 0x1F) + (c3 & 0x1F);

        GRAPHIC_RAM[row_offset + px] =
            (uint16_t)(((r >> 2) << 11) | ((g >> 2) << 5) | (b >> 2));
      } else {
        GRAPHIC_RAM[row_offset + px] = sample_mandelbrot(x0, y0, density);
      }
      x0 += scale;
    }
    y0 += scale;
  }
}

// ----------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------
int main(void) {
  init_palette();

  uint32_t active_page = 0;

  int center_x = -3072; // -0.75 in Q4.12
  int center_y = 0;
  int scale = 38;

  int needs_redraw = 1;
  int use_ssaa = 0;
  int show_help = 1;
  int color_density = 16;

  while (1) {
    if (needs_redraw) {
      uint32_t back_page = active_page ^ 1;

      render_mandelbrot(back_page, center_x, center_y, scale, use_ssaa,
                        color_density);

      if (show_help) {
        draw_help_window(back_page);
      }

      active_page = back_page;
      *PAGE_REG = active_page;
      needs_redraw = 0;
    }

    if (*KEY_STAT & 0x1) {
      uint8_t key = (uint8_t)(*KEY_DATA & 0xFF);
      int move_step = (scale * 15);

      if (key == 'w' || key == 'W') {
        center_y -= move_step;
        needs_redraw = 1;
      } else if (key == 's' || key == 'S') {
        center_y += move_step;
        needs_redraw = 1;
      } else if (key == 'a' || key == 'A') {
        center_x -= move_step;
        needs_redraw = 1;
      } else if (key == 'd' || key == 'D') {
        center_x += move_step;
        needs_redraw = 1;
      }

      else if (key == 'i' || key == 'I' || key == '+') {
        int new_scale = (scale * 3) >> 2;
        scale = (new_scale > 0) ? new_scale : 1;
        needs_redraw = 1;
      } else if (key == 'o' || key == 'O' || key == '-') {
        int new_scale = (scale * 5) >> 2;
        if (new_scale == scale)
          new_scale++;
        scale = new_scale;
        needs_redraw = 1;
      }

      else if (key == 'k' || key == 'K' || key == '[') {
        max_iter += 20;
        needs_redraw = 1;
      } else if (key == 'j' || key == 'J' || key == ']') {
        if (max_iter > 1) {
          max_iter -= 20;
          if (max_iter < 1)
            max_iter = 1;
          needs_redraw = 1;
        }
      }

      else if (key == 'c' || key == 'C') {
        if (color_density > 1) {
          color_density--;
          needs_redraw = 1;
        }
      } else if (key == 'v' || key == 'V') {
        if (color_density < 128) {
          color_density++;
          needs_redraw = 1;
        }
      }

      // Palette Preset Switcher
      else if (key == 'p' || key == 'P') {
        active_palette_type = (active_palette_type + 1) % 3;
        init_palette();
        needs_redraw = 1;
      }

      else if (key == 't' || key == 'T') {
        use_ssaa = !use_ssaa;
        needs_redraw = 1;
      } else if (key == 'h' || key == 'H') {
        show_help = !show_help;
        needs_redraw = 1;
      } else if (key == 'r' || key == 'R') {
        center_x = -3072;
        center_y = 0;
        scale = 38;
        max_iter = 40;
        use_ssaa = 0;
        color_density = 16;
        active_palette_type = 0;
        init_palette();
        needs_redraw = 1;
      } else if (key == 'q' || key == 'Q' || key == 27)
        break;
    }
  }

  *PAGE_REG = 0;
  return 0;
}