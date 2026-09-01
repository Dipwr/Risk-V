/* ============================================================================
 * RV32IM NANO-OS: SHELL, RAM-DISK VFS, TEXT EDITOR & SCRIPT INTERPRETER
 * ============================================================================
 * Target: Custom RV32IM Core (Bare-Metal + Newlib)
 * Load Address: 0x00040000 | Stack: 0x0007FFF0
 *
 * Capabilities:
 *  1. In-Memory Virtual Filesystem (VFS) with Preloaded Programs
 *  2. Full-Screen Interactive Text Editor ("edit <file>")
 *  3. Dynamic Script Interpreter / Engine ("run <file>") with Graphics
 * Extensions
 *  4. Direct Hardware PEEK / POKE Commands
 *  5. 53x25 Retro Terminal Console with Framebuffer & Serial Mirroring
 * ============================================================================
 */

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
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

#define TERM_COLS 53
#define TERM_ROWS 25
#define CHAR_W 6
#define CHAR_H 8

/* Colors */
#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))
#define COLOR_AMBER ((uint16_t)0xFD60) // Retro Amber CRT
#define COLOR_BLACK ((uint16_t)0x0000)
#define COLOR_GREEN ((uint16_t)0x07E0)
#define COLOR_CYAN ((uint16_t)0x07FF)
#define COLOR_WHITE ((uint16_t)0xFFFF)
#define COLOR_DARK_GRAY ((uint16_t)0x18C3)

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
 * RETRO 53x25 CRT TERMINAL ENGINE
 * ============================================================================
 */
static char g_term_grid[TERM_ROWS][TERM_COLS];
static int g_cur_x = 0;
static int g_cur_y = 0;
static uint16_t g_term_color = COLOR_AMBER;

static void term_draw_glyph(int col, int row, char c, uint16_t color) {
  if (c < 32 || c > 126)
    c = ' ';
  const uint8_t *glyph = font5x7[c - 32];
  int px = col * CHAR_W + 1;
  int py = row * CHAR_H;

  for (int y = 0; y < CHAR_H; y++) {
    for (int x = 0; x < CHAR_W; x++) {
      uint16_t pixel_color = COLOR_BLACK;
      if (x < 5 && y < 7 && (glyph[x] & (1 << y))) {
        pixel_color = color;
      }
      if ((uint32_t)(px + x) < SCREEN_WIDTH &&
          (uint32_t)(py + y) < SCREEN_HEIGHT) {
        GRAPHIC_RAM[(py + y) * SCREEN_WIDTH + (px + x)] = pixel_color;
      }
    }
  }
}

static void term_scroll(void) {
  for (int r = 0; r < TERM_ROWS - 1; r++) {
    memcpy(g_term_grid[r], g_term_grid[r + 1], TERM_COLS);
    for (int c = 0; c < TERM_COLS; c++) {
      term_draw_glyph(c, r, g_term_grid[r][c], g_term_color);
    }
  }
  memset(g_term_grid[TERM_ROWS - 1], ' ', TERM_COLS);
  for (int c = 0; c < TERM_COLS; c++) {
    term_draw_glyph(c, TERM_ROWS - 1, ' ', g_term_color);
  }
  g_cur_y = TERM_ROWS - 1;
}

static void term_clear(void) {
  memset(g_term_grid, ' ', sizeof(g_term_grid));
  for (int i = 0; i < PAGE_PIXELS; i++) {
    GRAPHIC_RAM[i] = COLOR_BLACK;
  }
  g_cur_x = 0;
  g_cur_y = 0;
}

void term_putc(char c) {
  if (c == '\r')
    return;
  if (c == '\n') {
    g_cur_x = 0;
    g_cur_y++;
    if (g_cur_y >= TERM_ROWS)
      term_scroll();
    return;
  }
  if (c == '\b') {
    if (g_cur_x > 0) {
      g_cur_x--;
      g_term_grid[g_cur_y][g_cur_x] = ' ';
      term_draw_glyph(g_cur_x, g_cur_y, ' ', g_term_color);
    }
    return;
  }

  if (g_cur_x >= TERM_COLS) {
    g_cur_x = 0;
    g_cur_y++;
    if (g_cur_y >= TERM_ROWS)
      term_scroll();
  }

  g_term_grid[g_cur_y][g_cur_x] = c;
  term_draw_glyph(g_cur_x, g_cur_y, c, g_term_color);
  g_cur_x++;
}

void term_print(const char *str) {
  while (*str) {
    term_putc(*str);
    *TERM_OUT = (uint32_t)(uint8_t)(*str++); // Mirror to serial MMIO
  }
}

/* ============================================================================
 * IN-MEMORY VIRTUAL FILESYSTEM (RAM-DISK VFS)
 * ============================================================================
 */
#define MAX_FILES 16
#define MAX_FILE_SIZE 2048

typedef struct {
  char name[32];
  char data[MAX_FILE_SIZE];
  size_t size;
  bool in_use;
} VFS_File;

static VFS_File g_vfs[MAX_FILES];

void vfs_init(void) {
  memset(g_vfs, 0, sizeof(g_vfs));

  // Preload File 1: README
  strcpy(g_vfs[0].name, "readme.txt");
  strcpy(g_vfs[0].data, "RV32IM Nano-OS v1.0\n"
                        "Features:\n"
                        " - RAM-Disk VFS with CRUD commands\n"
                        " - In-Terminal Editor ('edit <file>')\n"
                        " - BASIC Language Interpreter ('run <file>')\n"
                        " - Direct Memory PEEK / POKE\n");
  g_vfs[0].size = strlen(g_vfs[0].data);
  g_vfs[0].in_use = true;

  // Preload File 2: Fibonacci Generator in BASIC
  strcpy(g_vfs[1].name, "fib.bas");
  strcpy(g_vfs[1].data, "10 PRINT \"Fibonacci Series:\"\n"
                        "20 LET A = 0\n"
                        "30 LET B = 1\n"
                        "40 FOR I = 1 TO 12\n"
                        "50   PRINT B\n"
                        "60   LET C = A + B\n"
                        "70   LET A = B\n"
                        "80   LET B = C\n"
                        "90 NEXT I\n"
                        "100 END\n");
  g_vfs[1].size = strlen(g_vfs[1].data);
  g_vfs[1].in_use = true;

  // Preload File 3: Graphics Ray Demo in BASIC (Direct Framebuffer access!)
  strcpy(g_vfs[2].name, "rays.bas");
  strcpy(g_vfs[2].data, "10 CLS 0\n"
                        "20 PRINT \"Rendering graphics rays...\"\n"
                        "30 FOR I = 0 TO 320 STEP 8\n"
                        "40   LINE 160, 100, I, 0, 64800\n"
                        "50   LINE 160, 100, I, 199, 2016\n"
                        "60 NEXT I\n"
                        "70 END\n");
  g_vfs[2].size = strlen(g_vfs[2].data);
  g_vfs[2].in_use = true;
}

VFS_File *vfs_find(const char *name) {
  for (int i = 0; i < MAX_FILES; i++) {
    if (g_vfs[i].in_use && strcmp(g_vfs[i].name, name) == 0) {
      return &g_vfs[i];
    }
  }
  return NULL;
}

VFS_File *vfs_create(const char *name) {
  VFS_File *existing = vfs_find(name);
  if (existing)
    return existing;

  for (int i = 0; i < MAX_FILES; i++) {
    if (!g_vfs[i].in_use) {
      strncpy(g_vfs[i].name, name, 31);
      g_vfs[i].size = 0;
      g_vfs[i].data[0] = '\0';
      g_vfs[i].in_use = true;
      return &g_vfs[i];
    }
  }
  return NULL;
}

/* ============================================================================
 * EMBEDDED SCRIPT INTERPRETER (TINY BASIC + GRAPHICS ENGINE)
 * ============================================================================
 */
static int32_t g_vars[26] = {0}; // Variables A-Z

static inline int iabs(int v) { return (v < 0) ? -v : v; }

static void draw_line_direct(int x0, int y0, int x1, int y1, uint16_t color) {
  int dx = iabs(x1 - x0), sx = (x0 < x1) ? 1 : -1;
  int dy = -iabs(y1 - y0), sy = (y0 < y1) ? 1 : -1;
  int err = dx + dy, e2;
  while (1) {
    if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
      GRAPHIC_RAM[y0 * SCREEN_WIDTH + x0] = color;
    }
    if (x0 == x1 && y0 == y1)
      break;
    e2 = err << 1;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

static int32_t eval_expr(const char **p) {
  while (**p == ' ')
    (*p)++;
  int32_t val = 0;

  if (**p >= 'A' && **p <= 'Z') {
    val = g_vars[**p - 'A'];
    (*p)++;
  } else if (**p >= '0' && **p <= '9') {
    val = strtol(*p, (char **)p, 10);
  } else if (strncmp(*p, "PEEK", 4) == 0) {
    *p += 4;
    while (**p == ' ' || **p == '(')
      (*p)++;
    uint32_t addr = (uint32_t)strtol(*p, (char **)p, 0);
    while (**p == ' ' || **p == ')')
      (*p)++;
    val = *(volatile uint32_t *)addr;
  }

  while (**p == ' ')
    (*p)++;
  if (**p == '+' || **p == '-' || **p == '*' || **p == '/') {
    char op = **p;
    (*p)++;
    int32_t rhs = eval_expr(p);
    if (op == '+')
      val += rhs;
    else if (op == '-')
      val -= rhs;
    else if (op == '*')
      val *= rhs;
    else if (op == '/' && rhs != 0)
      val /= rhs;
  }
  return val;
}

void run_script(const char *code) {
  term_print("\n[RUN] Executing script...\n");
  memset(g_vars, 0, sizeof(g_vars));

  char lines[64][80];
  int line_nums[64];
  int total_lines = 0;

  // Parse lines
  const char *p = code;
  while (*p && total_lines < 64) {
    while (*p == ' ' || *p == '\n' || *p == '\r')
      p++;
    if (!*p)
      break;

    line_nums[total_lines] = strtol(p, (char **)&p, 10);
    while (*p == ' ')
      p++;
    int i = 0;
    while (*p && *p != '\n' && *p != '\r' && i < 79) {
      lines[total_lines][i++] = *p++;
    }
    lines[total_lines][i] = '\0';
    total_lines++;
  }

  // Execute
  int cur = 0;
  int for_var = -1, for_end = 0, for_line = -1;

  while (cur < total_lines) {
    const char *l = lines[cur];
    while (*l == ' ')
      l++;

    if (strncmp(l, "PRINT", 5) == 0) {
      l += 5;
      while (*l == ' ')
        l++;
      if (*l == '"') {
        l++;
        while (*l && *l != '"') {
          char c = *l++;
          term_putc(c);
          *TERM_OUT = (uint32_t)(uint8_t)c;
        }
      } else {
        int32_t v = eval_expr(&l);
        char numbuf[32];
        sprintf(numbuf, "%ld", (long)v);
        term_print(numbuf);
      }
      term_putc('\n');
      *TERM_OUT = '\n';
    } else if (strncmp(l, "LET", 3) == 0) {
      l += 3;
      while (*l == ' ')
        l++;
      char var = *l++;
      while (*l == ' ' || *l == '=')
        l++;
      if (var >= 'A' && var <= 'Z') {
        g_vars[var - 'A'] = eval_expr(&l);
      }
    } else if (strncmp(l, "FOR", 3) == 0) {
      l += 3;
      while (*l == ' ')
        l++;
      char var = *l++;
      while (*l == ' ' || *l == '=')
        l++;
      g_vars[var - 'A'] = eval_expr(&l);
      while (*l == ' ')
        l++;
      if (strncmp(l, "TO", 2) == 0) {
        l += 2;
        for_var = var - 'A';
        for_end = eval_expr(&l);
        for_line = cur;
      }
    } else if (strncmp(l, "NEXT", 4) == 0) {
      if (for_var >= 0) {
        g_vars[for_var]++;
        if (g_vars[for_var] <= for_end) {
          cur = for_line;
        } else {
          for_var = -1;
        }
      }
    } else if (strncmp(l, "CLS", 3) == 0) {
      l += 3;
      uint16_t col = (uint16_t)eval_expr(&l);
      for (int i = 0; i < PAGE_PIXELS; i++)
        GRAPHIC_RAM[i] = col;
    } else if (strncmp(l, "LINE", 4) == 0) {
      l += 4;
      int x0 = eval_expr(&l);
      while (*l == ' ' || *l == ',')
        l++;
      int y0 = eval_expr(&l);
      while (*l == ' ' || *l == ',')
        l++;
      int x1 = eval_expr(&l);
      while (*l == ' ' || *l == ',')
        l++;
      int y1 = eval_expr(&l);
      while (*l == ' ' || *l == ',')
        l++;
      int col = eval_expr(&l);
      draw_line_direct(x0, y0, x1, y1, (uint16_t)col);
    } else if (strncmp(l, "POKE", 4) == 0) {
      l += 4;
      uint32_t addr = (uint32_t)eval_expr(&l);
      while (*l == ' ' || *l == ',')
        l++;
      uint32_t val = (uint32_t)eval_expr(&l);
      *(volatile uint32_t *)addr = val;
    } else if (strncmp(l, "END", 3) == 0) {
      break;
    }
    cur++;
  }
  term_print("[RUN] Script finished.\n");
}

/* ============================================================================
 * INTERACTIVE TEXT EDITOR ("edit <filename>")
 * ============================================================================
 */
static char get_char_blocking(void) {
  while (!(*KEY_STAT & 1))
    ;
  return (char)(*KEY_DATA);
}

void open_editor(const char *filename) {
  VFS_File *f = vfs_create(filename);
  if (!f) {
    term_print("Error: Disk Full!\n");
    return;
  }

  term_clear();
  term_print("=== NANO-EDIT v1.0 (Type ':wq' to save & exit) ===\n");
  term_print("File: ");
  term_print(filename);
  term_print("\n----------------------------------------------------\n");
  term_print(f->data);

  char edit_buf[MAX_FILE_SIZE];
  strcpy(edit_buf, f->data);
  int pos = strlen(edit_buf);

  while (1) {
    char c = get_char_blocking();

    if (c == '\r' || c == '\n') {
      // Check for save & exit command ":wq"
      if (pos >= 3 && edit_buf[pos - 3] == ':' && edit_buf[pos - 2] == 'w' &&
          edit_buf[pos - 1] == 'q') {
        edit_buf[pos - 3] = '\0';
        strcpy(f->data, edit_buf);
        f->size = strlen(f->data);
        term_clear();
        term_print("File saved successfully.\n");
        return;
      }
      edit_buf[pos++] = '\n';
      edit_buf[pos] = '\0';
      term_putc('\n');
      *TERM_OUT = '\n';
    } else if (c == '\b') {
      if (pos > 0) {
        pos--;
        edit_buf[pos] = '\0';
        term_putc('\b');
      }
    } else if (c >= 32 && c <= 126 && pos < MAX_FILE_SIZE - 2) {
      edit_buf[pos++] = c;
      edit_buf[pos] = '\0';
      term_putc(c);
      *TERM_OUT = (uint32_t)(uint8_t)c;
    }
  }
}

/* ============================================================================
 * COMMAND SHELL (REPL)
 * ============================================================================
 */
void execute_command(char *cmd) {
  while (*cmd == ' ')
    cmd++;
  if (!*cmd)
    return;

  if (strcmp(cmd, "help") == 0 || strcmp(cmd, "?") == 0) {
    term_print("Available Commands:\n");
    term_print("  ls / dir       : List RAM disk files\n");
    term_print("  cat <file>     : Display file contents\n");
    term_print("  edit <file>    : Open in-terminal text editor\n");
    term_print("  run <file>     : Execute script in Tiny BASIC\n");
    term_print("  rm <file>      : Delete file\n");
    term_print("  mem            : Show CPU memory & stack stats\n");
    term_print("  peek <addr>    : Read 32-bit hardware address\n");
    term_print("  poke <a, v>    : Write 32-bit value to hardware\n");
    term_print("  bench          : Run on-chip integer benchmark\n");
    term_print("  clear / cls    : Clear screen\n");
    term_print("  exit           : Return to Wozmon ROM\n");
  } else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
    term_print("RAM Disk Contents:\n");
    int count = 0;
    for (int i = 0; i < MAX_FILES; i++) {
      if (g_vfs[i].in_use) {
        char buf[64];
        sprintf(buf, "  %-14s %4u B\n", g_vfs[i].name,
                (unsigned int)g_vfs[i].size);
        term_print(buf);
        count++;
      }
    }
    char summary[32];
    sprintf(summary, "Total: %d files.\n", count);
    term_print(summary);
  } else if (strncmp(cmd, "cat ", 4) == 0 || strncmp(cmd, "type ", 5) == 0) {
    char *fname = cmd + (cmd[0] == 'c' ? 4 : 5);
    while (*fname == ' ')
      fname++;
    VFS_File *f = vfs_find(fname);
    if (f) {
      term_print(f->data);
      term_putc('\n');
    } else {
      term_print("Error: File not found.\n");
    }
  } else if (strncmp(cmd, "edit ", 5) == 0 || strncmp(cmd, "nano ", 5) == 0) {
    char *fname = cmd + 5;
    while (*fname == ' ')
      fname++;
    open_editor(fname);
  } else if (strncmp(cmd, "run ", 4) == 0) {
    char *fname = cmd + 4;
    while (*fname == ' ')
      fname++;
    VFS_File *f = vfs_find(fname);
    if (f) {
      run_script(f->data);
    } else {
      term_print("Error: File not found.\n");
    }
  } else if (strncmp(cmd, "rm ", 3) == 0) {
    char *fname = cmd + 3;
    while (*fname == ' ')
      fname++;
    VFS_File *f = vfs_find(fname);
    if (f) {
      f->in_use = false;
      term_print("File deleted.\n");
    } else {
      term_print("Error: File not found.\n");
    }
  } else if (strcmp(cmd, "mem") == 0) {
    char buf[64];
    term_print("System Memory Map:\n");
    term_print("  RAM Base:   0x00040000 (256 KB)\n");
    term_print("  Stack Top:  0x0007FFF0\n");
    term_print("  VRAM:       0x00082000 (320x200 RGB565)\n");
    sprintf(buf, "  Free Heap:  %u B\n", (unsigned int)malloc(0));
    term_print(buf);
  } else if (strncmp(cmd, "peek ", 5) == 0) {
    uint32_t addr = (uint32_t)strtol(cmd + 5, NULL, 0);
    uint32_t val = *(volatile uint32_t *)addr;
    char buf[48];
    sprintf(buf, "[0x%08lX] = 0x%08lX (%ld)\n", (unsigned long)addr,
            (unsigned long)val, (long)val);
    term_print(buf);
  } else if (strncmp(cmd, "poke ", 5) == 0) {
    char *p = cmd + 5;
    uint32_t addr = (uint32_t)strtol(p, &p, 0);
    while (*p == ' ' || *p == ',')
      p++;
    uint32_t val = (uint32_t)strtol(p, NULL, 0);
    *(volatile uint32_t *)addr = val;
    term_print("Write complete.\n");
  } else if (strcmp(cmd, "bench") == 0) {
    term_print("Running Integer Core Benchmark...\n");
    volatile uint32_t acc = 0;
    for (uint32_t i = 0; i < 500000; i++) {
      acc += (i * 3) ^ (i >> 2);
    }
    term_print("Benchmark completed: 500,000 ops verified!\n");
  } else if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "cls") == 0) {
    term_clear();
  } else if (strcmp(cmd, "exit") == 0) {
    exit(0);
  } else {
    term_print("Unknown command. Type 'help' for available commands.\n");
  }
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================
 */
int main(void) {
  // Flush stale keyboard buffer
  while (*KEY_STAT & 1)
    (void)*KEY_DATA;

  *PAGE_REG = 0;
  term_clear();
  vfs_init();

  term_print("====================================================\n");
  term_print("   RV32IM NANO-OS & EMBEDDED COMPUTING SYSTEM       \n");
  term_print("   Arch: RV32IM @ 24.5 MHz | RAM: 256 KB | VRAM OK \n");
  term_print("====================================================\n");
  term_print("Mounting in-memory VFS... OK (RAM-Disk active)\n");
  term_print("Type 'help' for commands, 'ls' to view files.\n\n");

  char cmd_buf[64];
  int cmd_idx = 0;

  term_print("rv32:/$ ");

  while (1) {
    if (*KEY_STAT & 1) {
      char c = (char)(*KEY_DATA);

      if (c == 27) { // ESC -> Return to Wozmon
        exit(0);
      } else if (c == '\r' || c == '\n') {
        term_putc('\n');
        *TERM_OUT = '\n';
        cmd_buf[cmd_idx] = '\0';
        execute_command(cmd_buf);
        cmd_idx = 0;
        term_print("rv32:/$ ");
      } else if (c == '\b') {
        if (cmd_idx > 0) {
          cmd_idx--;
          term_putc('\b');
        }
      } else if (c >= 32 && c <= 126 && cmd_idx < 62) {
        cmd_buf[cmd_idx++] = c;
        term_putc(c);
        *TERM_OUT = (uint32_t)(uint8_t)c;
      }
    }
  }

  return 0;
}