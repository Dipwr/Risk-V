/* ============================================================================
 * RV32IM RETRO DESKTOP ENVIRONMENT & APP SUITE (MICROUI + NEWLIB)
 * ============================================================================
 * Applications Included:
 *  1. Theme & Style Studio (Live RGBA customizer & Windows 95/Cyberpunk
 * presets)
 *  2. Interactive GUI Calculator
 *  3. Mini Paint Canvas (Mouse drawing with color palette)
 *  4. File Explorer (Collapsible tree view & text file reader)
 *  5. Interactive System Terminal
 *  6. Desktop Start Bar & Popup Application Menu
 * ============================================================================
 */

#include "microui.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MMIO Hardware Registers */
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)
#define MOUSE_X ((volatile uint32_t *)0x00080028)
#define MOUSE_Y ((volatile uint32_t *)0x0008002C)
#define MOUSE_BTN ((volatile uint32_t *)0x00080030)
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

static mu_Context ctx;

/* ============================================================================
 * EMBEDDED 5x7 FONT
 * ============================================================================
 */
static const uint8_t font5x7[95][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, {0x00, 0x00, 0x5F, 0x00, 0x00},
    {0x00, 0x07, 0x00, 0x07, 0x00}, {0x14, 0x7F, 0x14, 0x7F, 0x14},
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, {0x23, 0x13, 0x08, 0x64, 0x62},
    {0x36, 0x49, 0x55, 0x22, 0x50}, {0x00, 0x05, 0x03, 0x00, 0x00},
    {0x00, 0x1C, 0x22, 0x41, 0x00}, {0x00, 0x41, 0x22, 0x1C, 0x00},
    {0x14, 0x08, 0x3E, 0x08, 0x14}, {0x08, 0x08, 0x3E, 0x08, 0x08},
    {0x00, 0x50, 0x30, 0x00, 0x00}, {0x08, 0x08, 0x08, 0x08, 0x08},
    {0x00, 0x60, 0x60, 0x00, 0x00}, {0x20, 0x10, 0x08, 0x04, 0x02},
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, {0x00, 0x42, 0x7F, 0x40, 0x00},
    {0x42, 0x61, 0x51, 0x49, 0x46}, {0x21, 0x41, 0x45, 0x4B, 0x31},
    {0x18, 0x14, 0x12, 0x7F, 0x10}, {0x27, 0x45, 0x45, 0x45, 0x39},
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, {0x01, 0x71, 0x09, 0x05, 0x03},
    {0x36, 0x49, 0x49, 0x49, 0x36}, {0x06, 0x49, 0x49, 0x29, 0x1E},
    {0x00, 0x36, 0x36, 0x00, 0x00}, {0x00, 0x56, 0x36, 0x00, 0x00},
    {0x08, 0x14, 0x22, 0x41, 0x00}, {0x14, 0x14, 0x14, 0x14, 0x14},
    {0x00, 0x41, 0x22, 0x14, 0x08}, {0x02, 0x01, 0x51, 0x09, 0x06},
    {0x32, 0x49, 0x79, 0x41, 0x3E}, {0x7E, 0x11, 0x11, 0x11, 0x7E},
    {0x7F, 0x49, 0x49, 0x49, 0x36}, {0x3E, 0x41, 0x41, 0x41, 0x22},
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, {0x7F, 0x49, 0x49, 0x49, 0x41},
    {0x7F, 0x09, 0x09, 0x09, 0x01}, {0x3E, 0x41, 0x49, 0x49, 0x7A},
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, {0x00, 0x41, 0x7F, 0x41, 0x00},
    {0x20, 0x40, 0x41, 0x3F, 0x01}, {0x7F, 0x08, 0x14, 0x22, 0x41},
    {0x7F, 0x40, 0x40, 0x40, 0x40}, {0x7F, 0x02, 0x0C, 0x02, 0x7F},
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, {0x3E, 0x41, 0x41, 0x41, 0x3E},
    {0x7F, 0x09, 0x09, 0x09, 0x06}, {0x3E, 0x41, 0x51, 0x21, 0x5E},
    {0x7F, 0x09, 0x19, 0x29, 0x46}, {0x46, 0x49, 0x49, 0x49, 0x31},
    {0x01, 0x01, 0x7F, 0x01, 0x01}, {0x3F, 0x40, 0x40, 0x40, 0x3F},
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, {0x3F, 0x40, 0x38, 0x40, 0x3F},
    {0x63, 0x14, 0x08, 0x14, 0x63}, {0x07, 0x08, 0x70, 0x08, 0x07},
    {0x61, 0x51, 0x49, 0x45, 0x43}, {0x00, 0x7F, 0x41, 0x41, 0x00},
    {0x02, 0x04, 0x08, 0x10, 0x20}, {0x00, 0x41, 0x41, 0x7F, 0x00},
    {0x04, 0x02, 0x01, 0x02, 0x04}, {0x40, 0x40, 0x40, 0x40, 0x40},
    {0x00, 0x01, 0x02, 0x04, 0x00}, {0x20, 0x54, 0x54, 0x54, 0x78},
    {0x7F, 0x48, 0x44, 0x44, 0x38}, {0x38, 0x44, 0x44, 0x44, 0x20},
    {0x38, 0x44, 0x44, 0x48, 0x7F}, {0x38, 0x54, 0x54, 0x54, 0x18},
    {0x08, 0x7E, 0x09, 0x01, 0x02}, {0x0C, 0x52, 0x52, 0x52, 0x3E},
    {0x7F, 0x08, 0x04, 0x04, 0x78}, {0x00, 0x44, 0x7D, 0x40, 0x00},
    {0x20, 0x40, 0x44, 0x3D, 0x00}, {0x7F, 0x10, 0x28, 0x44, 0x00},
    {0x00, 0x41, 0x7F, 0x40, 0x00}, {0x7C, 0x04, 0x18, 0x04, 0x78},
    {0x7C, 0x08, 0x04, 0x04, 0x78}, {0x38, 0x44, 0x44, 0x44, 0x38},
    {0x7C, 0x14, 0x14, 0x14, 0x08}, {0x08, 0x14, 0x14, 0x18, 0x7C},
    {0x7C, 0x08, 0x04, 0x04, 0x08}, {0x48, 0x54, 0x54, 0x54, 0x20},
    {0x04, 0x3F, 0x44, 0x40, 0x20}, {0x3C, 0x40, 0x40, 0x20, 0x7C},
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, {0x3C, 0x40, 0x30, 0x40, 0x3C},
    {0x44, 0x28, 0x10, 0x28, 0x44}, {0x0C, 0x50, 0x50, 0x50, 0x3C},
    {0x44, 0x64, 0x54, 0x4C, 0x44}, {0x00, 0x08, 0x36, 0x41, 0x00},
    {0x00, 0x00, 0x7F, 0x00, 0x00}, {0x00, 0x41, 0x36, 0x08, 0x00},
    {0x08, 0x08, 0x2A, 0x1C, 0x08}};

/* ============================================================================
 * CLIPPING & GRAPHICS DRIVERS
 * ============================================================================
 */
static mu_Rect g_clip = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

static inline uint16_t mu_color_to_rgb565(mu_Color c) {
  return MAKE_RGB(c.r >> 3, c.g >> 2, c.b >> 3);
}

static inline void put_pixel_clipped(int page, int x, int y, uint16_t color) {
  if (x >= g_clip.x && x < (g_clip.x + g_clip.w) && y >= g_clip.y &&
      y < (g_clip.y + g_clip.h) && (uint32_t)x < SCREEN_WIDTH &&
      (uint32_t)y < SCREEN_HEIGHT) {
    GRAPHIC_RAM[(page * PAGE_PIXELS) + (y * SCREEN_WIDTH) + x] = color;
  }
}

static void fill_rect_clipped(int page, mu_Rect r, mu_Color color) {
  uint16_t c565 = mu_color_to_rgb565(color);
  int x0 = (r.x < g_clip.x) ? g_clip.x : r.x;
  int y0 = (r.y < g_clip.y) ? g_clip.y : r.y;
  int x1 =
      (r.x + r.w > g_clip.x + g_clip.w) ? (g_clip.x + g_clip.w) : (r.x + r.w);
  int y1 =
      (r.y + r.h > g_clip.y + g_clip.h) ? (g_clip.y + g_clip.h) : (r.y + r.h);

  if (x0 >= x1 || y0 >= y1)
    return;

  uint32_t page_offset = page * PAGE_PIXELS;
  for (int y = y0; y < y1; y++) {
    for (int x = x0; x < x1; x++) {
      GRAPHIC_RAM[page_offset + (y * SCREEN_WIDTH) + x] = c565;
    }
  }
}

static void draw_text_clipped(int page, const char *str, int x, int y,
                              mu_Color color) {
  uint16_t c565 = mu_color_to_rgb565(color);
  int cur_x = x;
  while (*str) {
    char c = *str++;
    if (c >= 32 && c <= 126) {
      const uint8_t *glyph = font5x7[c - 32];
      for (int col = 0; col < 5; col++) {
        uint8_t line = glyph[col];
        for (int row = 0; row < 7; row++) {
          if (line & (1 << row)) {
            put_pixel_clipped(page, cur_x + col, y + row, c565);
          }
        }
      }
    }
    cur_x += 6;
  }
}

static int text_width_cb(mu_Font font, const char *str, int len) {
  (void)font;
  if (len < 0)
    len = (int)strlen(str);
  return len * 6;
}

static int text_height_cb(mu_Font font) {
  (void)font;
  return 8;
}

static void render_microui_commands(int page, mu_Context *mu_ctx) {
  mu_Command *cmd = NULL;
  g_clip = (mu_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

  while (mu_next_command(mu_ctx, &cmd)) {
    switch (cmd->type) {
    case MU_COMMAND_RECT:
      fill_rect_clipped(page, cmd->rect.rect, cmd->rect.color);
      break;
    case MU_COMMAND_TEXT:
      draw_text_clipped(page, cmd->text.str, cmd->text.pos.x, cmd->text.pos.y,
                        cmd->text.color);
      break;
    case MU_COMMAND_ICON:
      fill_rect_clipped(
          page, (mu_Rect){cmd->icon.rect.x + 2, cmd->icon.rect.y + 2, 6, 6},
          cmd->icon.color);
      break;
    case MU_COMMAND_CLIP:
      g_clip = cmd->clip.rect;
      break;
    }
  }
}

/* Mouse cursor pointer */
static void draw_mouse_cursor(int page, int mx, int my) {
  for (int i = 0; i < 7; i++) {
    put_pixel_clipped(page, mx + i, my, MAKE_RGB(31, 63, 31));
    put_pixel_clipped(page, mx, my + i, MAKE_RGB(31, 63, 31));
    put_pixel_clipped(page, mx + i, my + i, MAKE_RGB(31, 63, 31));
    put_pixel_clipped(page, mx + i + 1, my + i, MAKE_RGB(0, 0, 0));
  }
}

/* ============================================================================
 * PRESET DESKTOP THEMES
 * ============================================================================
 */
static uint16_t g_desktop_bg = MAKE_RGB(0, 16, 16); // Default Windows 95 Teal

void set_theme(int theme_id) {
  if (theme_id == 0) {                  // Windows 95 Classic
    g_desktop_bg = MAKE_RGB(0, 32, 32); // Teal background
    ctx.style->colors[MU_COLOR_WINDOWBG] = mu_color(192, 192, 192, 255);
    ctx.style->colors[MU_COLOR_TITLEBG] = mu_color(0, 0, 128, 255);
    ctx.style->colors[MU_COLOR_TITLETEXT] = mu_color(255, 255, 255, 255);
    ctx.style->colors[MU_COLOR_PANELBG] = mu_color(220, 220, 220, 255);
    ctx.style->colors[MU_COLOR_BUTTON] = mu_color(192, 192, 192, 255);
    ctx.style->colors[MU_COLOR_BUTTONHOVER] = mu_color(216, 216, 216, 255);
    ctx.style->colors[MU_COLOR_BUTTONFOCUS] = mu_color(160, 160, 160, 255);
    ctx.style->colors[MU_COLOR_BASE] = mu_color(255, 255, 255, 255);
    ctx.style->colors[MU_COLOR_TEXT] = mu_color(0, 0, 0, 255);
    ctx.style->colors[MU_COLOR_BORDER] = mu_color(64, 64, 64, 255);
  } else if (theme_id == 1) { // Cyberpunk Dark Neon
    g_desktop_bg = MAKE_RGB(1, 2, 4);
    ctx.style->colors[MU_COLOR_WINDOWBG] = mu_color(24, 24, 32, 255);
    ctx.style->colors[MU_COLOR_TITLEBG] = mu_color(0, 128, 160, 255);
    ctx.style->colors[MU_COLOR_TITLETEXT] = mu_color(255, 255, 255, 255);
    ctx.style->colors[MU_COLOR_PANELBG] = mu_color(16, 16, 24, 255);
    ctx.style->colors[MU_COLOR_BUTTON] = mu_color(40, 48, 64, 255);
    ctx.style->colors[MU_COLOR_BUTTONHOVER] = mu_color(64, 80, 112, 255);
    ctx.style->colors[MU_COLOR_BUTTONFOCUS] = mu_color(0, 180, 220, 255);
    ctx.style->colors[MU_COLOR_BASE] = mu_color(32, 36, 48, 255);
    ctx.style->colors[MU_COLOR_TEXT] = mu_color(220, 240, 255, 255);
    ctx.style->colors[MU_COLOR_BORDER] = mu_color(0, 180, 220, 255);
  } else if (theme_id == 2) { // Retro Macintosh Platinum
    g_desktop_bg = MAKE_RGB(16, 32, 16);
    ctx.style->colors[MU_COLOR_WINDOWBG] = mu_color(230, 230, 230, 255);
    ctx.style->colors[MU_COLOR_TITLEBG] = mu_color(180, 180, 190, 255);
    ctx.style->colors[MU_COLOR_TITLETEXT] = mu_color(0, 0, 0, 255);
    ctx.style->colors[MU_COLOR_PANELBG] = mu_color(245, 245, 245, 255);
    ctx.style->colors[MU_COLOR_BUTTON] = mu_color(220, 220, 220, 255);
    ctx.style->colors[MU_COLOR_BUTTONHOVER] = mu_color(240, 240, 240, 255);
    ctx.style->colors[MU_COLOR_BUTTONFOCUS] = mu_color(150, 150, 160, 255);
    ctx.style->colors[MU_COLOR_BASE] = mu_color(255, 255, 255, 255);
    ctx.style->colors[MU_COLOR_TEXT] = mu_color(20, 20, 20, 255);
    ctx.style->colors[MU_COLOR_BORDER] = mu_color(100, 100, 100, 255);
  }
}

/* ============================================================================
 * APP 1: STYLE & THEME STUDIO (From the Official MicroUI Showcase)
 * ============================================================================
 */
static void render_style_editor(mu_Context *mu_ctx) {
  if (mu_begin_window(mu_ctx, "Theme Studio", mu_rect(10, 20, 150, 160))) {
    mu_layout_row(mu_ctx, 1, (int[]){-1}, 0);

    mu_label(mu_ctx, "Presets:");
    mu_layout_row(mu_ctx, 3, (int[]){42, 42, -1}, 0);
    if (mu_button(mu_ctx, "Win95"))
      set_theme(0);
    if (mu_button(mu_ctx, "Cyber"))
      set_theme(1);
    if (mu_button(mu_ctx, "Mac"))
      set_theme(2);

    mu_layout_row(mu_ctx, 1, (int[]){-1}, 0);
    mu_label(mu_ctx, "Customize Window Colors:");

    static const char *color_names[] = {"Text",     "Border",     "Window BG",
                                        "Title BG", "Title Text", "Panel BG",
                                        "Button",   "Btn Hover",  "Btn Focus"};
    static int selected_color = 3; // Title BG default

    for (int i = 0; i < 9; i++) {
      if (mu_button(mu_ctx, color_names[i])) {
        selected_color = i;
      }
    }

    // RGBA Color Sliders for selected UI component
    mu_Color *c = &mu_ctx->style->colors[selected_color];
    char label_buf[32];
    sprintf(label_buf, "Editing: %s", color_names[selected_color]);
    mu_label(mu_ctx, label_buf);

    float r = c->r, g = c->g, b = c->b;
    mu_layout_row(mu_ctx, 2, (int[]){20, -1}, 0);
    mu_label(mu_ctx, "R:");
    mu_slider(mu_ctx, &r, 0, 255);
    mu_label(mu_ctx, "G:");
    mu_slider(mu_ctx, &g, 0, 255);
    mu_label(mu_ctx, "B:");
    mu_slider(mu_ctx, &b, 0, 255);
    c->r = (uint8_t)r;
    c->g = (uint8_t)g;
    c->b = (uint8_t)b;

    mu_end_window(mu_ctx);
  }
}

/* ============================================================================
 * APP 2: GUI CALCULATOR
 * ============================================================================
 */
static double g_calc_val = 0;
static double g_calc_accum = 0;
static char g_calc_op = 0;
static bool g_calc_reset_next = true;
static char g_calc_display[32] = "0";

static void calc_press_digit(int d) {
  if (g_calc_reset_next) {
    g_calc_val = d;
    g_calc_reset_next = false;
  } else {
    g_calc_val = g_calc_val * 10 + d;
  }
  sprintf(g_calc_display, "%.0f", g_calc_val);
}

static void calc_press_op(char op) {
  g_calc_accum = g_calc_val;
  g_calc_op = op;
  g_calc_reset_next = true;
}

static void calc_press_equals(void) {
  if (g_calc_op == '+')
    g_calc_val = g_calc_accum + g_calc_val;
  else if (g_calc_op == '-')
    g_calc_val = g_calc_accum - g_calc_val;
  else if (g_calc_op == '*')
    g_calc_val = g_calc_accum * g_calc_val;
  else if (g_calc_op == '/' && g_calc_val != 0)
    g_calc_val = g_calc_accum / g_calc_val;
  g_calc_op = 0;
  g_calc_reset_next = true;
  sprintf(g_calc_display, "%.2f", g_calc_val);
}

static void render_calculator(mu_Context *mu_ctx) {
  if (mu_begin_window(mu_ctx, "Calculator", mu_rect(170, 20, 135, 140))) {
    // Display screen
    mu_layout_row(mu_ctx, 1, (int[]){-1}, 18);
    mu_draw_control_text(mu_ctx, g_calc_display, mu_layout_next(mu_ctx),
                         MU_COLOR_TEXT, MU_OPT_ALIGNRIGHT);

    // Keypad grid
    mu_layout_row(mu_ctx, 4, (int[]){26, 26, 26, -1}, 18);
    if (mu_button(mu_ctx, "7"))
      calc_press_digit(7);
    if (mu_button(mu_ctx, "8"))
      calc_press_digit(8);
    if (mu_button(mu_ctx, "9"))
      calc_press_digit(9);
    if (mu_button(mu_ctx, "/"))
      calc_press_op('/');

    if (mu_button(mu_ctx, "4"))
      calc_press_digit(4);
    if (mu_button(mu_ctx, "5"))
      calc_press_digit(5);
    if (mu_button(mu_ctx, "6"))
      calc_press_digit(6);
    if (mu_button(mu_ctx, "*"))
      calc_press_op('*');

    if (mu_button(mu_ctx, "1"))
      calc_press_digit(1);
    if (mu_button(mu_ctx, "2"))
      calc_press_digit(2);
    if (mu_button(mu_ctx, "3"))
      calc_press_digit(3);
    if (mu_button(mu_ctx, "-"))
      calc_press_op('-');

    if (mu_button(mu_ctx, "C")) {
      g_calc_val = 0;
      g_calc_accum = 0;
      g_calc_op = 0;
      sprintf(g_calc_display, "0");
    }
    if (mu_button(mu_ctx, "0"))
      calc_press_digit(0);
    if (mu_button(mu_ctx, "="))
      calc_press_equals();
    if (mu_button(mu_ctx, "+"))
      calc_press_op('+');

    mu_end_window(mu_ctx);
  }
}

/* ============================================================================
 * APP 3: MINI PAINT STUDIO
 * ============================================================================
 */
#define CANVAS_W 24
#define CANVAS_H 16
static uint8_t g_canvas[CANVAS_W * CANVAS_H] = {0};
static uint8_t g_brush_color = 1;

static inline bool point_in_rect(mu_Rect r, int x, int y) {
  return x >= r.x && x < (r.x + r.w) && y >= r.y && y < (r.y + r.h);
}

static void render_paint_studio(mu_Context *mu_ctx) {
  if (mu_begin_window(mu_ctx, "Paint Studio", mu_rect(15, 30, 145, 145))) {
    mu_layout_row(mu_ctx, 4, (int[]){26, 26, 26, -1}, 12);
    if (mu_button(mu_ctx, "Blk"))
      g_brush_color = 0;
    if (mu_button(mu_ctx, "Red"))
      g_brush_color = 1;
    if (mu_button(mu_ctx, "Grn"))
      g_brush_color = 2;
    if (mu_button(mu_ctx, "Blu"))
      g_brush_color = 3;

    mu_layout_row(mu_ctx, 1, (int[]){-1}, 0);
    if (mu_button(mu_ctx, "Clear Canvas")) {
      memset(g_canvas, 0, sizeof(g_canvas));
    }

    // Custom Canvas Drawing Area
    mu_Rect r = mu_layout_next(mu_ctx);
    r.w = CANVAS_W * 4;
    r.h = CANVAS_H * 4;
    mu_draw_rect(mu_ctx, r, mu_color(255, 255, 255, 255));

    // Interactive mouse drawing inside canvas
    if (mu_ctx->mouse_down &&
        point_in_rect(r, mu_ctx->mouse_pos.x, mu_ctx->mouse_pos.y)) {
      int cx = (mu_ctx->mouse_pos.x - r.x) / 4;
      int cy = (mu_ctx->mouse_pos.y - r.y) / 4;
      if (cx >= 0 && cx < CANVAS_W && cy >= 0 && cy < CANVAS_H) {
        g_canvas[cy * CANVAS_W + cx] = g_brush_color;
      }
    }

    // Render pixel grid
    for (int y = 0; y < CANVAS_H; y++) {
      for (int x = 0; x < CANVAS_W; x++) {
        uint8_t c = g_canvas[y * CANVAS_W + x];
        if (c == 0)
          continue;
        mu_Color col = (c == 1)   ? mu_color(220, 20, 20, 255)
                       : (c == 2) ? mu_color(20, 200, 20, 255)
                                  : mu_color(20, 40, 220, 255);
        mu_draw_rect(mu_ctx, mu_rect(r.x + x * 4, r.y + y * 4, 4, 4), col);
      }
    }

    mu_end_window(mu_ctx);
  }
}

/* ============================================================================
 * APP 4: FILE EXPLORER & TEXT VIEWER (Tree-View Hierarchy)
 * ============================================================================
 */
static char g_file_preview[128] = "Click a file to view contents.";

static void render_file_explorer(mu_Context *mu_ctx) {
  if (mu_begin_window(mu_ctx, "File Explorer", mu_rect(160, 30, 145, 145))) {
    mu_layout_row(mu_ctx, 1, (int[]){-1}, 0);

    if (mu_begin_treenode(mu_ctx, "/ Documents")) {
      if (mu_button(mu_ctx, "  readme.txt")) {
        strcpy(g_file_preview, "RV32IM Bare-Metal OS\nRunning on Custom "
                               "Verilated Core.\nSpeed: 24.5 MHz.");
      }
      if (mu_button(mu_ctx, "  todo.txt")) {
        strcpy(g_file_preview, "1. Build 3D Raycaster\n2. Add Sound "
                               "Synthesizer\n3. Enjoy MicroUI!");
      }
      mu_end_treenode(mu_ctx);
    }

    if (mu_begin_treenode(mu_ctx, "/ System")) {
      if (mu_button(mu_ctx, "  boot.s")) {
        strcpy(g_file_preview,
               ".section .text.boot\n_start: li sp, 0x0007FFF0\ncall main");
      }
      if (mu_button(mu_ctx, "  memory.map")) {
        strcpy(g_file_preview,
               "ROM:  0x00000000\nRAM:  0x00040000 (256KB)\nVRAM: 0x00082000");
      }
      mu_end_treenode(mu_ctx);
    }

    mu_layout_row(mu_ctx, 1, (int[]){-1}, 40);
    mu_text(mu_ctx, g_file_preview);

    mu_end_window(mu_ctx);
  }
}

/* ============================================================================
 * APP 5: INTERACTIVE SYSTEM TERMINAL
 * ============================================================================
 */
static char g_term_input[48] = "";
static char g_term_log[128] =
    "RV-OS Terminal Ready.\nType 'help' for commands.";

static void render_terminal(mu_Context *mu_ctx) {
  if (mu_begin_window(mu_ctx, "Terminal", mu_rect(30, 30, 160, 140))) {
    mu_layout_row(mu_ctx, 1, (int[]){-1}, 60);
    mu_text(mu_ctx, g_term_log);

    mu_layout_row(mu_ctx, 2, (int[]){-45, -1}, 0);
    mu_textbox(mu_ctx, g_term_input, sizeof(g_term_input));

    if (mu_button(mu_ctx, "Exec")) {
      if (strcmp(g_term_input, "clear") == 0) {
        g_term_log[0] = '\0';
      } else if (strcmp(g_term_input, "help") == 0) {
        strcpy(g_term_log, "Commands: clear, help, alloc, stats, win95");
      } else if (strcmp(g_term_input, "alloc") == 0) {
        void *p = malloc(1024);
        sprintf(g_term_log, "malloc(1024) -> %p\nHeap free ok.", p);
        free(p);
      } else if (strcmp(g_term_input, "win95") == 0) {
        set_theme(0);
        strcpy(g_term_log, "Applied Windows 95 Theme!");
      } else {
        sprintf(g_term_log, "Executed: %s", g_term_input);
      }
      g_term_input[0] = '\0';
    }
    mu_end_window(mu_ctx);
  }
}

/* ============================================================================
 * DESKTOP START BAR & WINDOW MANAGER
 * ============================================================================
 */
static bool g_win_theme = true;
static bool g_win_calc = true;
static bool g_win_paint = false;
static bool g_win_files = false;
static bool g_win_term = false;

static void render_desktop(mu_Context *mu_ctx) {
  // 1. Windows 95 Style Bottom Taskbar
  if (mu_begin_window_ex(mu_ctx, "Taskbar",
                         mu_rect(0, SCREEN_HEIGHT - 16, SCREEN_WIDTH, 16),
                         MU_OPT_NOTITLE | MU_OPT_NORESIZE)) {
    mu_layout_row(mu_ctx, 5, (int[]){55, 55, 55, 55, -1}, 12);

    if (mu_button(mu_ctx, "[Start]")) {
      mu_open_popup(mu_ctx, "StartMenu");
    }
    if (mu_button(mu_ctx, "Calc"))
      g_win_calc ^= 1;
    if (mu_button(mu_ctx, "Paint"))
      g_win_paint ^= 1;
    if (mu_button(mu_ctx, "Files"))
      g_win_files ^= 1;
    mu_label(mu_ctx, "RV32IM @ 24.5MHz");

    // Popup Start Menu
    if (mu_begin_popup(mu_ctx, "StartMenu")) {
      if (mu_button(mu_ctx, "Theme Studio")) {
        g_win_theme = true;
      }
      if (mu_button(mu_ctx, "Calculator")) {
        g_win_calc = true;
      }
      if (mu_button(mu_ctx, "Paint Studio")) {
        g_win_paint = true;
      }
      if (mu_button(mu_ctx, "File Explorer")) {
        g_win_files = true;
      }
      if (mu_button(mu_ctx, "Terminal")) {
        g_win_term = true;
      }
      if (mu_button(mu_ctx, "Exit to Wozmon")) {
        exit(0);
      }
      mu_end_popup(mu_ctx);
    }

    mu_end_window(mu_ctx);
  }

  // 2. Render Active Windows
  if (g_win_theme)
    render_style_editor(mu_ctx);
  if (g_win_calc)
    render_calculator(mu_ctx);
  if (g_win_paint)
    render_paint_studio(mu_ctx);
  if (g_win_files)
    render_file_explorer(mu_ctx);
  if (g_win_term)
    render_terminal(mu_ctx);
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================
 */
int main(void) {
  uint32_t active_page = 0;

  // Flush stale keyboard buffer
  while (*KEY_STAT & 1)
    (void)*KEY_DATA;

  printf("[System] Booting MicroUI Desktop...\n");

  mu_init(&ctx);
  ctx.text_width = text_width_cb;
  ctx.text_height = text_height_cb;

  // Default to Classic Windows 95 Theme
  set_theme(0);

  *PAGE_REG = 0;
  int last_mbtn = 0;

  while (1) {
    uint32_t back_page = active_page ^ 1;

    // 1. Read Mouse & Keyboard MMIO
    int mx = (int)(*MOUSE_X);
    int my = (int)(*MOUSE_Y);
    int mbtn = (int)(*MOUSE_BTN);

    mu_input_mousemove(&ctx, mx, my);

    if ((mbtn & 1) && !(last_mbtn & 1)) {
      mu_input_mousedown(&ctx, mx, my, MU_MOUSE_LEFT);
    } else if (!(mbtn & 1) && (last_mbtn & 1)) {
      mu_input_mouseup(&ctx, mx, my, MU_MOUSE_LEFT);
    }
    last_mbtn = mbtn;

    // Read Keyboard
    if (*KEY_STAT & 1) {
      char c = (char)(*KEY_DATA);
      if (c == 27)
        break; // ESC -> Return to Wozmon
      if (c == '\r')
        c = '\n';
      char str_buf[2] = {c, '\0'};
      mu_input_text(&ctx, str_buf);
    }

    // 2. Render Desktop Application State
    mu_begin(&ctx);
    render_desktop(&ctx);
    mu_end(&ctx);

    // 3. Clear Desktop Background Color
    uint32_t bg32 = (uint32_t)g_desktop_bg | ((uint32_t)g_desktop_bg << 16);
    volatile uint32_t *p32 =
        (volatile uint32_t *)&GRAPHIC_RAM[back_page * PAGE_PIXELS];
    for (int i = 0; i < PAGE_PIXELS / 2; i++) {
      p32[i] = bg32;
    }

    // 4. Blit Draw Commands & Mouse Pointer
    render_microui_commands(back_page, &ctx);
    draw_mouse_cursor(back_page, mx, my);

    // 5. Flip Framebuffer Page
    *PAGE_REG = back_page;
    active_page = back_page;
  }

  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
  return 0;
}