#include "contiki-conf.h"
#include "ctk/ctk-draw.h"
#include "ctk/ctk-mouse.h"
#include "ctk/ctk.h"
#include <string.h>

#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)
#define MOUSE_X ((volatile uint32_t *)0x00080028)
#define MOUSE_Y ((volatile uint32_t *)0x0008002C)
#define MOUSE_BTN ((volatile uint32_t *)0x00080030)
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)
#define GRAPHIC_RAM32 ((volatile uint32_t *)0x00082000)

#define FB_WIDTH 320
#define FB_HEIGHT 200
#define FB_PIXELS (FB_WIDTH * FB_HEIGHT)

// Color Scheme Structure
struct ctk_theme_palette {
  uint16_t desktop;
  uint16_t win_bg;
  uint16_t win_border;
  uint16_t title_act;
  uint16_t title_ina;
  uint16_t text_fg;
  uint16_t text_hi;
  uint16_t btn_bg;
  uint16_t menu_bg;
  uint16_t menu_act;
};

// Built-in Color Themes
static const struct ctk_theme_palette themes[] = {
    // 0: Classic Royal Blue (Default)
    {0x001F, 0xCE79, 0x0000, 0x001F, 0x8410, 0x0000, 0xFFFF, 0xAD55, 0xFFFF,
     0x001F},
    // 1: Cyberpunk Neon
    {0x1082, 0x2124, 0xF81F, 0xF81F, 0x4208, 0x07FF, 0xFFFF, 0x418A, 0x2124,
     0xF81F},
    // 2: Amber Retro CRT
    {0x0000, 0x2100, 0xFC00, 0xFC00, 0x8200, 0xFE40, 0x0000, 0x8200, 0x3180,
     0xFC00},
    // 3: Slate Modern
    {0x39E7, 0xEF7D, 0x2104, 0x4A69, 0x8410, 0x1082, 0xFFFF, 0xCE59, 0xFFFF,
     0x4A69}};

static struct ctk_theme_palette current_theme = {0x001F, 0xCE79, 0x0000, 0x001F,
                                                 0x8410, 0x0000, 0xFFFF, 0xAD55,
                                                 0xFFFF, 0x001F};

void ctk_arch_set_theme(int theme_id) {
  if (theme_id >= 0 && theme_id < 4) {
    current_theme = themes[theme_id];
    ctk_draw_clear(0, CTK_CONF_SCREEN_HEIGHT);
  }
}

// Official IBM VGA 8x8 Font
static const uint8_t font8x8_basic[95][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ' '
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // !
    {0x36, 0x36, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00}, // "
    {0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00}, // #
    {0x18, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x18, 0x00}, // $
    {0x00, 0x63, 0x66, 0x0C, 0x18, 0x33, 0x63, 0x00}, // %
    {0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00}, // &
    {0x30, 0x30, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00}, // '
    {0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00}, // (
    {0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00}, // )
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // *
    {0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00}, // +
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30}, // ,
    {0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00}, // -
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, // .
    {0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, // /
    {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00}, // 0
    {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00}, // 1
    {0x3C, 0x66, 0x06, 0x0C, 0x18, 0x30, 0x7E, 0x00}, // 2
    {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00}, // 3
    {0x0C, 0x1C, 0x3C, 0x6C, 0xFE, 0x0C, 0x0C, 0x00}, // 4
    {0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00}, // 5
    {0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00}, // 6
    {0x7E, 0x66, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x00}, // 7
    {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00}, // 8
    {0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00}, // 9
    {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00}, // :
    {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 0x00}, // ;
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // <
    {0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00}, // =
    {0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00}, // >
    {0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00}, // ?
    {0x3C, 0x66, 0x6E, 0x6E, 0x60, 0x3E, 0x00, 0x00}, // @
    {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, // A
    {0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00}, // B
    {0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}, // C
    {0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00}, // D
    {0xFE, 0x60, 0x60, 0x7C, 0x60, 0x60, 0xFE, 0x00}, // E
    {0xFE, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00}, // F
    {0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3E, 0x00}, // G
    {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // H
    {0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00}, // I
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C, 0x00}, // J
    {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}, // K
    {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xFE, 0x00}, // L
    {0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x00}, // M
    {0x66, 0x76, 0x7E, 0x6E, 0x66, 0x66, 0x66, 0x00}, // N
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // O
    {0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}, // P
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x0E, 0x00}, // Q
    {0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x00}, // R
    {0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00}, // S
    {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // T
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // U
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // V
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x36, 0x00}, // W
    {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00}, // X
    {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}, // Y
    {0xFE, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFE, 0x00}, // Z
    {0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00}, // [
    {0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00}, // '\'
    {0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00}, // ]
    {0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00}, // ^
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // _
    {0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00}, // `
    {0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00}, // a
    {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x7C, 0x00}, // b
    {0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 0x00}, // c
    {0x06, 0x06, 0x3E, 0x66, 0x66, 0x66, 0x3E, 0x00}, // d
    {0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00}, // e
    {0x1C, 0x30, 0x7C, 0x30, 0x30, 0x30, 0x30, 0x00}, // f
    {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x3C}, // g
    {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00}, // h
    {0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00}, // i
    {0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x38}, // j
    {0x60, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0x00}, // k
    {0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // l
    {0x00, 0x00, 0x6C, 0xFE, 0xD6, 0xC6, 0xC6, 0x00}, // m
    {0x00, 0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00}, // n
    {0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00}, // o
    {0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60}, // p
    {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x06}, // q
    {0x00, 0x00, 0x7C, 0x66, 0x60, 0x60, 0x60, 0x00}, // r
    {0x00, 0x00, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x00}, // s
    {0x18, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x0E, 0x00}, // t
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00}, // u
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // v
    {0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00}, // w
    {0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00}, // x
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x3C}, // y
    {0x00, 0x00, 0x7E, 0x0C, 0x18, 0x30, 0x7E, 0x00}, // z
    {0x0E, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0E, 0x00}, // {
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // |
    {0x70, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x70, 0x00}, // }
    {0x3A, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // ~
};

// Fast Unrolled Glyph Renderer (Page 0 Direct Write Only)
static void draw_char(int col, int row, char c, uint16_t fg, uint16_t bg) {
  if (col < 0 || col >= CTK_CONF_SCREEN_WIDTH || row < 0 ||
      row >= CTK_CONF_SCREEN_HEIGHT)
    return;
  const uint8_t *glyph =
      (c >= 32 && c <= 126) ? font8x8_basic[c - 32] : font8x8_basic[0];
  int sx = col * 8;
  int sy = row * 8;

  for (int r = 0; r < 8; r++) {
    uint8_t bits = glyph[r];
    volatile uint16_t *line = &GRAPHIC_RAM[(sy + r) * FB_WIDTH + sx];
    line[0] = (bits & 0x80) ? fg : bg;
    line[1] = (bits & 0x40) ? fg : bg;
    line[2] = (bits & 0x20) ? fg : bg;
    line[3] = (bits & 0x10) ? fg : bg;
    line[4] = (bits & 0x08) ? fg : bg;
    line[5] = (bits & 0x04) ? fg : bg;
    line[6] = (bits & 0x02) ? fg : bg;
    line[7] = (bits & 0x01) ? fg : bg;
  }
}

static void draw_str(int col, int row, const char *str, uint16_t fg,
                     uint16_t bg) {
  if (!str)
    return;
  while (*str && col < CTK_CONF_SCREEN_WIDTH) {
    draw_char(col++, row, *str++, fg, bg);
  }
}

void ctk_draw_init(void) {
  *PAGE_REG = 0;
  ctk_draw_clear(0, CTK_CONF_SCREEN_HEIGHT);
}

// 32-Bit Fast Rectangular Desktop Fill (15x Speedup)
void ctk_draw_clear(unsigned char clipy1, unsigned char clipy2) {
  uint32_t bg32 =
      ((uint32_t)current_theme.desktop << 16) | current_theme.desktop;
  int start_word = (clipy1 * 8) * (FB_WIDTH / 2);
  int end_word = (clipy2 * 8) * (FB_WIDTH / 2);

  for (int i = start_word; i < end_word; i++) {
    GRAPHIC_RAM32[i] = bg32;
  }
}

// 32-Bit Fast Window Client Area Fill
void ctk_draw_clear_window(struct ctk_window *w, unsigned char focus,
                           unsigned char clipy1, unsigned char clipy2) {
  (void)focus;
  uint32_t bg32 = ((uint32_t)current_theme.win_bg << 16) | current_theme.win_bg;
  int start_col = w->x + 1;
  int num_cols = w->w;
  int start_row = w->y + 2;
  int end_row = w->y + w->h + 2;

  int py1 = start_row * 8;
  int py2 = end_row * 8;
  int clip_py1 = clipy1 * 8;
  int clip_py2 = clipy2 * 8;

  if (py1 < clip_py1)
    py1 = clip_py1;
  if (py2 > clip_py2)
    py2 = clip_py2;

  int word_offset = start_col * 4;
  int words_per_line = num_cols * 4;

  for (int py = py1; py < py2; py++) {
    volatile uint32_t *line32 =
        &GRAPHIC_RAM32[py * (FB_WIDTH / 2) + word_offset];
    for (int w_idx = 0; w_idx < words_per_line; w_idx++) {
      line32[w_idx] = bg32;
    }
  }
}

void ctk_draw_widget(struct ctk_widget *widget, unsigned char focus,
                     unsigned char clipy1, unsigned char clipy2) {
  struct ctk_window *w = widget->window;
  int x = w->x + 1 + widget->x;
  int y = w->y + 2 + widget->y;

  if (y < clipy1 || y >= clipy2)
    return;

  if (widget->type == CTK_WIDGET_BUTTON) {
    struct ctk_button *b = (struct ctk_button *)widget;
    draw_char(x, y, '[', current_theme.text_fg, current_theme.btn_bg);
    draw_str(x + 1, y, b->text,
             focus ? current_theme.text_hi : current_theme.text_fg,
             focus ? current_theme.title_act : current_theme.btn_bg);
    draw_char(x + 1 + strlen(b->text), y, ']', current_theme.text_fg,
              current_theme.btn_bg);
  } else if (widget->type == CTK_WIDGET_LABEL) {
    struct ctk_label *l = (struct ctk_label *)widget;
    if (l->text) {
      draw_str(x, y, l->text, current_theme.text_fg, current_theme.win_bg);
    }
  } else if (widget->type == CTK_WIDGET_TEXTENTRY) {
    struct ctk_textentry *t = (struct ctk_textentry *)widget;
    draw_char(x, y, '|', current_theme.win_border, current_theme.win_bg);
    if (t->text) {
      draw_str(x + 1, y, t->text,
               focus ? current_theme.text_hi : current_theme.text_fg,
               focus ? current_theme.title_act : current_theme.win_bg);
    }
    int text_len = t->text ? strlen(t->text) : 0;
    for (int i = text_len; i < t->len; i++) {
      draw_char(x + 1 + i, y, ' ', current_theme.text_fg,
                focus ? current_theme.title_act : current_theme.win_bg);
    }
    draw_char(x + 1 + t->len, y, '|', current_theme.win_border,
              current_theme.win_bg);
  } else if (widget->type == CTK_WIDGET_SEPARATOR) {
    for (int i = 0; i < widget->w; i++) {
      draw_char(x + i, y, '-', current_theme.win_border, current_theme.win_bg);
    }
  }
}

// Full Window Draw
void ctk_draw_window(struct ctk_window *w, unsigned char focus,
                     unsigned char clipy1, unsigned char clipy2,
                     unsigned char draw_border) {
  int x1 = w->x;
  int y1 = w->y + 1;
  int x2 = w->x + w->w + 1;
  int y2 = w->y + w->h + 2;
  struct ctk_widget *widget;

  // 1. Clear interior client area
  ctk_draw_clear_window(w, focus, clipy1, clipy2);

  // 2. Draw border
  if (draw_border) {
    for (int x = x1; x <= x2; x++) {
      if (y1 >= clipy1 && y1 < clipy2)
        draw_char(x, y1, '=', current_theme.text_hi,
                  focus ? current_theme.title_act : current_theme.title_ina);
      if (y2 >= clipy1 && y2 < clipy2)
        draw_char(x, y2, '-', current_theme.win_border, current_theme.win_bg);
    }
    for (int y = y1 + 1; y < y2; y++) {
      if (y >= clipy1 && y < clipy2) {
        draw_char(x1, y, '|', current_theme.win_border, current_theme.win_bg);
        draw_char(x2, y, '|', current_theme.win_border, current_theme.win_bg);
      }
    }
  }

  // 3. Draw Title & Close Button [X]
  if (w->title != NULL && y1 >= clipy1 && y1 < clipy2) {
    draw_str(x1 + 1, y1, w->title, current_theme.text_hi,
             focus ? current_theme.title_act : current_theme.title_ina);
    draw_str(x2 - 3, y1, "[X]", current_theme.text_hi,
             focus ? current_theme.title_act : current_theme.title_ina);
  }

  // 4. Draw ALL widgets immediately
  for (widget = w->inactive; widget != NULL; widget = widget->next) {
    ctk_draw_widget(widget, 0, clipy1, clipy2);
  }
  for (widget = w->active; widget != NULL; widget = widget->next) {
    if (widget != w->focused) {
      ctk_draw_widget(widget, 0, clipy1, clipy2);
    }
  }
  if (w->focused != NULL) {
    ctk_draw_widget(w->focused, focus, clipy1, clipy2);
  }
}

void ctk_draw_dialog(struct ctk_window *dialog) {
  ctk_draw_window(dialog, 1, 0, CTK_CONF_SCREEN_HEIGHT, 1);
}

// Spaced Menu Bar Drawer
void ctk_draw_menus(struct ctk_menus *menus) {
  // 1. Clear top menu bar row (Row 0)
  for (int col = 0; col < CTK_CONF_SCREEN_WIDTH; col++) {
    draw_char(col, 0, ' ', current_theme.text_fg, current_theme.menu_bg);
  }

  // 2. Draw user menus on the left (menus->menus->next)
  int col = 1;
  for (struct ctk_menu *m = menus->menus->next; m != NULL; m = m->next) {
    int is_open = (m == menus->open);
    int len = m->titlelen ? m->titlelen : strlen(m->title);

    // Draw menu title on the bar
    for (int i = 0; i < len; i++) {
      draw_char(col + i, 0, m->title[i],
                is_open ? current_theme.text_hi : current_theme.text_fg,
                is_open ? current_theme.menu_act : current_theme.menu_bg);
    }

    // If this menu is open, draw its dropdown popup box
    if (is_open) {
      int box_x = col;
      if (box_x + CTK_CONF_MENUWIDTH > CTK_CONF_SCREEN_WIDTH) {
        box_x = CTK_CONF_SCREEN_WIDTH - CTK_CONF_MENUWIDTH;
      }
      for (int i = 0; i < m->nitems; i++) {
        int item_y = 1 + i;
        int is_active = (i == m->active);
        uint16_t bg =
            is_active ? current_theme.menu_act : current_theme.menu_bg;
        uint16_t fg = is_active ? current_theme.text_hi : current_theme.text_fg;

        for (int c = box_x; c < box_x + CTK_CONF_MENUWIDTH; c++) {
          draw_char(c, item_y, ' ', fg, bg);
        }
        draw_str(box_x + 1, item_y, m->items[i].title, fg, bg);
      }
    }

    col += len;
  }

  // 3. Draw Desktop Menu on the far right (menus->desktopmenu)
  if (menus->desktopmenu != NULL) {
    struct ctk_menu *dm = menus->desktopmenu;
    int dm_len = dm->titlelen ? dm->titlelen : strlen(dm->title);
    int dm_x = CTK_CONF_SCREEN_WIDTH - dm_len;
    int is_open = (dm == menus->open);

    for (int i = 0; i < dm_len; i++) {
      draw_char(dm_x + i, 0, dm->title[i],
                is_open ? current_theme.text_hi : current_theme.text_fg,
                is_open ? current_theme.menu_act : current_theme.menu_bg);
    }

    if (is_open) {
      int box_x = CTK_CONF_SCREEN_WIDTH - CTK_CONF_MENUWIDTH;
      for (int i = 0; i < dm->nitems; i++) {
        int item_y = 1 + i;
        int is_active = (i == dm->active);
        uint16_t bg =
            is_active ? current_theme.menu_act : current_theme.menu_bg;
        uint16_t fg = is_active ? current_theme.text_hi : current_theme.text_fg;

        for (int c = box_x; c < box_x + CTK_CONF_MENUWIDTH; c++) {
          draw_char(c, item_y, ' ', fg, bg);
        }
        draw_str(box_x + 1, item_y, dm->items[i].title, fg, bg);
      }
    }
  }
}

unsigned char ctk_draw_width(void) { return CTK_CONF_SCREEN_WIDTH; }
unsigned char ctk_draw_height(void) { return CTK_CONF_SCREEN_HEIGHT; }

unsigned char ctk_draw_windowtitle_height = 1;
unsigned char ctk_draw_windowborder_height = 1;
unsigned char ctk_draw_windowborder_width = 1;

void ctk_mouse_init(void) {}
void ctk_mouse_show(void) {}
void ctk_mouse_hide(void) {}
unsigned short ctk_mouse_x(void) { return (unsigned short)(*MOUSE_X); }
unsigned short ctk_mouse_y(void) { return (unsigned short)(*MOUSE_Y); }
unsigned char ctk_mouse_xtoc(unsigned short x) {
  return (unsigned char)(x / 8);
}
unsigned char ctk_mouse_ytoc(unsigned short y) {
  return (unsigned char)(y / 8);
}
unsigned char ctk_mouse_button(void) { return (unsigned char)(*MOUSE_BTN & 1); }

unsigned char ctk_arch_keyavail(void) { return (unsigned char)(*KEY_STAT & 1); }
ctk_arch_key_t ctk_arch_getkey(void) {
  if (*KEY_STAT & 1)
    return (ctk_arch_key_t)(*KEY_DATA);
  return 0;
}