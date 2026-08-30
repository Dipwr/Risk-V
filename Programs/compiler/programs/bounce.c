/* ============================================================================
 * RV32IM BARE-METAL BOUNCING BOX / DVD LOGO SIMULATION (RGB565 UPDATED)
 * Target: Custom RV32IM Core (320x200 @ Double-Buffered 16-bit VRAM)
 * ============================================================================
 */

#include <stdint.h>

/* --- Hardware MMIO Registers --- */
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

/* 16-bit Packed VRAM Pointer (1 pixel per 2 bytes) */
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

/* --- Display & Viewport Setup --- */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT) // 64,000 pixels per page

#define BOX_WIDTH 32
#define BOX_HEIGHT 20

/* --- Color Palette (RGB565 format: 5-bit Red, 6-bit Green, 5-bit Blue) --- */
#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define COLOR_BLACK ((uint16_t)0x0000)
#define COLOR_RED MAKE_RGB(31, 0, 0)
#define COLOR_GREEN MAKE_RGB(0, 63, 0)
#define COLOR_BLUE MAKE_RGB(0, 0, 31)
#define COLOR_YELLOW MAKE_RGB(31, 63, 0)
#define COLOR_CYAN MAKE_RGB(0, 63, 31)
#define COLOR_MAGENTA MAKE_RGB(31, 0, 31)
#define COLOR_WHITE MAKE_RGB(31, 63, 31)

static const uint16_t color_palette[7] = {
    COLOR_RED,  COLOR_GREEN,   COLOR_BLUE, COLOR_YELLOW,
    COLOR_CYAN, COLOR_MAGENTA, COLOR_WHITE};

/* --- Terminal Output Helper --- */
void print_string(const char *str) {
  while (*str) {
    *TERM_OUT = (uint32_t)(*str++);
  }
}

/* --- Graphics Rendering Routines --- */
void clear_page(int page, uint16_t color) {
  uint32_t offset = page * PAGE_PIXELS;
  for (int i = 0; i < PAGE_PIXELS; i++) {
    GRAPHIC_RAM[offset + i] = color;
  }
}

void draw_rect(int page, int x, int y, int w, int h, uint16_t color) {
  uint32_t page_offset = page * PAGE_PIXELS;

  for (int dy = 0; dy < h; dy++) {
    int py = y + dy;
    if (py < 0 || py >= SCREEN_HEIGHT)
      continue;

    uint32_t row = page_offset + (py * SCREEN_WIDTH);
    for (int dx = 0; dx < w; dx++) {
      int px = x + dx;
      if (px >= 0 && px < SCREEN_WIDTH) {
        GRAPHIC_RAM[row + px] = color;
      }
    }
  }
}

/* --- Main Program --- */
int main(void) {
  print_string("[RV32IM Core] Bouncing Box Simulation (16-bit RGB565)\n");

  clear_page(0, COLOR_BLACK);
  clear_page(1, COLOR_BLACK);

  int x = 10, y = 10;
  int dx = 2, dy = 1;
  int color_idx = 0;
  uint32_t active_page = 0;

  while (1) {
    if (*KEY_STAT != 0) {
      uint32_t key = *KEY_DATA;
      (void)key;
      print_string("[Exiting to Wozmon...]\n");
      break;
    }

    uint32_t back_page = 1 - active_page;

    clear_page(back_page, COLOR_BLACK);

    x += dx;
    y += dy;

    int bounced = 0;
    if (x <= 0 || (x + BOX_WIDTH) >= SCREEN_WIDTH) {
      dx = -dx;
      bounced = 1;
    }
    if (y <= 0 || (y + BOX_HEIGHT) >= SCREEN_HEIGHT) {
      dy = -dy;
      bounced = 1;
    }

    if (bounced) {
      color_idx = (color_idx + 1) % 7;
    }

    draw_rect(back_page, x, y, BOX_WIDTH, BOX_HEIGHT, color_palette[color_idx]);

    *PAGE_REG = back_page;
    active_page = back_page;

    for (volatile int delay = 0; delay < 20000; delay++)
      ;
  }

  *PAGE_REG = 0;
  return 0;
}