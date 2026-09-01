/* ============================================================================
 * RV32IM C-NATIVE WORKSTATION (FreeRTOS + LittleFS + C4 Compiler Engine)
 * ============================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "c_engine.h"
#include "lfs.h"
#include "task.h"

/* MMIO Hardware */
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

/* ============================================================================
 * 1. 53x25 RETRO CRT TERMINAL
 * ============================================================================
 */
#define TERM_COLS 53
#define TERM_ROWS 25
#define CHAR_W 6
#define CHAR_H 8

#define COLOR_GREEN ((uint16_t)0x07E0) // Retro CRT Phosphor Green
#define COLOR_BLACK ((uint16_t)0x0000)

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

static char g_term_grid[TERM_ROWS][TERM_COLS];
static int g_cur_x = 0, g_cur_y = 0;

static void term_draw_glyph(int col, int row, char c, uint16_t color) {
  if (c < 32 || c > 126)
    c = ' ';
  const uint8_t *glyph = font5x7[c - 32];
  int px = col * CHAR_W + 1;
  int py = row * CHAR_H;

  for (int y = 0; y < CHAR_H; y++) {
    for (int x = 0; x < CHAR_W; x++) {
      uint16_t pixel = COLOR_BLACK;
      if (x < 5 && y < 7 && (glyph[x] & (1 << y))) {
        pixel = color;
      }
      if ((uint32_t)(px + x) < SCREEN_WIDTH &&
          (uint32_t)(py + y) < SCREEN_HEIGHT) {
        GRAPHIC_RAM[(py + y) * SCREEN_WIDTH + (px + x)] = pixel;
      }
    }
  }
}

static void term_scroll(void) {
  for (int r = 0; r < TERM_ROWS - 1; r++) {
    memcpy(g_term_grid[r], g_term_grid[r + 1], TERM_COLS);
    for (int c = 0; c < TERM_COLS; c++) {
      term_draw_glyph(c, r, g_term_grid[r][c], COLOR_GREEN);
    }
  }
  memset(g_term_grid[TERM_ROWS - 1], ' ', TERM_COLS);
  for (int c = 0; c < TERM_COLS; c++) {
    term_draw_glyph(c, TERM_ROWS - 1, ' ', COLOR_GREEN);
  }
  g_cur_y = TERM_ROWS - 1;
}

void term_clear(void) {
  memset(g_term_grid, ' ', sizeof(g_term_grid));
  for (int i = 0; i < PAGE_PIXELS; i++) {
    GRAPHIC_RAM[i] = COLOR_BLACK;
  }
  g_cur_x = 0;
  g_cur_y = 0;
}

/* Global function called by syscalls.c _write() */
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
      term_draw_glyph(g_cur_x, g_cur_y, ' ', COLOR_GREEN);
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
  term_draw_glyph(g_cur_x, g_cur_y, c, COLOR_GREEN);
  g_cur_x++;
}

/* ============================================================================
 * 2. ARM LITTLEFS RAM-DISK BLOCK DRIVER
 * ============================================================================
 */
#define RAM_BLOCK_SIZE 512
#define RAM_BLOCK_COUNT 96
static uint8_t ram_disk[RAM_BLOCK_SIZE * RAM_BLOCK_COUNT]
    __attribute__((aligned(8)));

static int lfs_ram_read(const struct lfs_config *c, lfs_block_t block,
                        lfs_off_t off, void *buffer, lfs_size_t size) {
  (void)c;
  memcpy(buffer, &ram_disk[block * RAM_BLOCK_SIZE + off], size);
  return 0;
}

static int lfs_ram_prog(const struct lfs_config *c, lfs_block_t block,
                        lfs_off_t off, const void *buffer, lfs_size_t size) {
  (void)c;
  memcpy(&ram_disk[block * RAM_BLOCK_SIZE + off], buffer, size);
  return 0;
}

static int lfs_ram_erase(const struct lfs_config *c, lfs_block_t block) {
  (void)c;
  memset(&ram_disk[block * RAM_BLOCK_SIZE], 0xFF, RAM_BLOCK_SIZE);
  return 0;
}

static int lfs_ram_sync(const struct lfs_config *c) {
  (void)c;
  return 0;
}

static lfs_t g_lfs;
static const struct lfs_config g_lfs_cfg = {
    .read = lfs_ram_read,
    .prog = lfs_ram_prog,
    .erase = lfs_ram_erase,
    .sync = lfs_ram_sync,
    .read_size = 16,
    .prog_size = 16,
    .block_size = RAM_BLOCK_SIZE,
    .block_count = RAM_BLOCK_COUNT,
    .cache_size = 64,
    .lookahead_size = 16,
    .block_cycles = 500,
};

static void vfs_write_file(const char *name, const char *content) {
  lfs_file_t file;
  if (lfs_file_open(&g_lfs, &file, name,
                    LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC) >= 0) {
    lfs_file_write(&g_lfs, &file, content, strlen(content));
    lfs_file_close(&g_lfs, &file);
  }
}

void init_filesystem(void) {
  printf("[VFS] Mounting ARM LittleFS RAM-Disk...\n");
  if (lfs_mount(&g_lfs, &g_lfs_cfg) < 0) {
    printf("[VFS] Formatting clean LittleFS filesystem...\n");
    lfs_format(&g_lfs, &g_lfs_cfg);
    lfs_mount(&g_lfs, &g_lfs_cfg);

    // Preload Starter C Programs onto the virtual disk
    vfs_write_file("hello.c",
                   "int main() {\n"
                   "    printf(\"Hello from C code compiled on RV32IM!\\n\");\n"
                   "    int sum = 0;\n"
                   "    int i = 1;\n"
                   "    while (i <= 10) {\n"
                   "        sum = sum + i;\n"
                   "        i++;\n"
                   "    }\n"
                   "    printf(\"Sum of 1..10 = %d\\n\", sum);\n"
                   "    return 0;\n"
                   "}\n");

    vfs_write_file(
        "graphics.c",
        "int main() {\n"
        "    clear_screen(0x0000);\n"
        "    printf(\"Drawing ray patterns to 320x200 VRAM...\\n\");\n"
        "    int i = 0;\n"
        "    while (i <= 320) {\n"
        "        draw_pixel(i, 100, 0x07E0);\n"
        "        i = i + 4;\n"
        "    }\n"
        "    printf(\"Draw finished!\\n\");\n"
        "    return 0;\n"
        "}\n");

    vfs_write_file("fib.c",
                   "int fib(int n) {\n"
                   "    if (n <= 1) return n;\n"
                   "    return fib(n - 1) + fib(n - 2);\n"
                   "}\n"
                   "int main() {\n"
                   "    printf(\"Recursive Fibonacci Benchmark:\\n\");\n"
                   "    int i = 0;\n"
                   "    while (i <= 8) {\n"
                   "        printf(\"F(%d) = %d\\n\", i, fib(i));\n"
                   "        i++;\n"
                   "    }\n"
                   "    return 0;\n"
                   "}\n");
  }
}

/* ============================================================================
 * 3. KILO FULL-SCREEN CODE EDITOR
 * ============================================================================
 */
static char get_char_blocking(void) {
  while (!(*KEY_STAT & 1)) {
    taskYIELD();
  }
  return (char)(*KEY_DATA);
}

void open_kilo_editor(const char *filename) {
  lfs_file_t file;
  char text_buf[2048] = "";
  int len = 0;

  if (lfs_file_open(&g_lfs, &file, filename, LFS_O_RDONLY) >= 0) {
    len = lfs_file_read(&g_lfs, &file, text_buf, sizeof(text_buf) - 1);
    text_buf[len] = '\0';
    lfs_file_close(&g_lfs, &file);
  }

  term_clear();
  printf("=== KILO TEXT EDITOR | File: %s ===\n", filename);
  printf("[Type text | Type ':wq' and press Enter to Save | ESC to Cancel]\n");
  printf("----------------------------------------------------\n");
  printf("%s", text_buf);

  int pos = len;

  while (1) {
    char c = get_char_blocking();

    if (c == 27) {
      term_clear();
      printf("[Kilo] Editing cancelled.\n");
      return;
    } else if (c == '\r' || c == '\n') {
      if (pos >= 3 && text_buf[pos - 3] == ':' && text_buf[pos - 2] == 'w' &&
          text_buf[pos - 1] == 'q') {
        text_buf[pos - 3] = '\0';
        vfs_write_file(filename, text_buf);
        term_clear();
        printf("[Kilo] '%s' saved to LittleFS successfully!\n", filename);
        return;
      }
      if (pos < (int)sizeof(text_buf) - 2) {
        text_buf[pos++] = '\n';
        text_buf[pos] = '\0';
        putchar('\n');
      }
    } else if (c == '\b') {
      if (pos > 0) {
        pos--;
        text_buf[pos] = '\0';
        putchar('\b');
      }
    } else if (c >= 32 && c <= 126 && pos < (int)sizeof(text_buf) - 2) {
      text_buf[pos++] = c;
      text_buf[pos] = '\0';
      putchar(c);
    }
  }
}

/* ============================================================================
 * 4. WORKSTATION COMMAND SHELL
 * ============================================================================
 */
void execute_shell_command(char *cmd) {
  while (*cmd == ' ')
    cmd++;
  if (!*cmd)
    return;

  if (strcmp(cmd, "help") == 0) {
    printf("RV32IM C-Workstation Commands:\n");
    printf("  ls / dir       : List files on LittleFS filesystem\n");
    printf("  cat <file.c>   : Print file contents\n");
    printf("  kilo <file.c>  : Open full-screen text editor\n");
    printf("  run <file.c>   : Compile and execute C program on-chip\n");
    printf("  rm <file>      : Delete file\n");
    printf("  df             : Display LittleFS disk usage\n");
    printf("  mem            : Display system RAM & heap state\n");
    printf("  clear          : Clear screen\n");
    printf("  exit           : Exit to Wozmon ROM\n");
  } else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
    lfs_dir_t dir;
    struct lfs_info info;
    if (lfs_dir_open(&g_lfs, &dir, "/") >= 0) {
      printf("Directory listing of /:\n");
      while (lfs_dir_read(&g_lfs, &dir, &info) > 0) {
        if (strcmp(info.name, ".") == 0 || strcmp(info.name, "..") == 0)
          continue;
        printf("  %-16s %4ld bytes\n", info.name, (long)info.size);
      }
      lfs_dir_close(&g_lfs, &dir);
    }
  } else if (strncmp(cmd, "cat ", 4) == 0) {
    char *fname = cmd + 4;
    while (*fname == ' ')
      fname++;
    lfs_file_t file;
    if (lfs_file_open(&g_lfs, &file, fname, LFS_O_RDONLY) >= 0) {
      char buf[128];
      int n;
      while ((n = lfs_file_read(&g_lfs, &file, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
      }
      printf("\n");
      lfs_file_close(&g_lfs, &file);
    } else {
      printf("Error: File '%s' not found.\n", fname);
    }
  } else if (strncmp(cmd, "kilo ", 5) == 0) {
    char *fname = cmd + 5;
    while (*fname == ' ')
      fname++;
    open_kilo_editor(fname);
  } else if (strncmp(cmd, "run ", 4) == 0) {
    char *fname = cmd + 4;
    while (*fname == ' ')
      fname++;
    lfs_file_t file;
    if (lfs_file_open(&g_lfs, &file, fname, LFS_O_RDONLY) >= 0) {
      lfs_soff_t sz = lfs_file_size(&g_lfs, &file);
      char *buf = malloc(sz + 1);
      if (buf) {
        lfs_file_read(&g_lfs, &file, buf, sz);
        buf[sz] = '\0';
        lfs_file_close(&g_lfs, &file);

        printf("[C4] Compiling and Executing '%s' on RV32IM...\n", fname);
        c_compile_and_run(buf);
        free(buf);
        printf("[C4] Finished execution.\n");
      }
    } else {
      printf("Error: Cannot open '%s'\n", fname);
    }
  } else if (strncmp(cmd, "rm ", 3) == 0) {
    char *fname = cmd + 3;
    while (*fname == ' ')
      fname++;
    if (lfs_remove(&g_lfs, fname) >= 0)
      printf("File '%s' deleted.\n", fname);
    else
      printf("Error: Could not delete '%s'\n", fname);
  } else if (strcmp(cmd, "df") == 0) {
    printf("LittleFS Disk Info:\n");
    printf("  Block Size:  %d Bytes\n", RAM_BLOCK_SIZE);
    printf("  Total Size:  %d KB (96 Blocks)\n",
           (RAM_BLOCK_SIZE * RAM_BLOCK_COUNT) / 1024);
  } else if (strcmp(cmd, "mem") == 0) {
    printf("RV32IM System Memory:\n");
    printf("  Physical RAM: 256 KB (0x00040000 - 0x0007FFFF)\n");
    printf("  FreeRTOS Heap Free: %u Bytes\n",
           (unsigned int)xPortGetFreeHeapSize());
  } else if (strcmp(cmd, "clear") == 0) {
    term_clear();
  } else if (strcmp(cmd, "exit") == 0) {
    exit(0);
  } else {
    printf("Unknown command '%s'. Type 'help' for command list.\n", cmd);
  }
}

/* ============================================================================
 * FREERTOS TASK 1: MAIN WORKSTATION SHELL
 * ============================================================================
 */
static void vTaskShell(void *pvParameters) {
  (void)pvParameters;

  term_clear();
  printf("========================================================\n");
  printf("   RV32IM C-NATIVE WORKSTATION (FreeRTOS + LittleFS)    \n");
  printf("   Core: RV32IM @ 24.5 MHz | 256 KB RAM | LittleFS OK   \n");
  printf("========================================================\n");
  printf("Type 'help' for commands, 'ls' to view files.\n\n");

  char cmd_buf[64];
  int cmd_idx = 0;

  printf("rv32:/$ ");

  while (1) {
    if (*KEY_STAT & 1) {
      char c = (char)(*KEY_DATA);

      if (c == 27) { // ESC -> Wozmon
        exit(0);
      } else if (c == '\r' || c == '\n') {
        putchar('\n');
        cmd_buf[cmd_idx] = '\0';
        execute_shell_command(cmd_buf);
        cmd_idx = 0;
        printf("rv32:/$ ");
      } else if (c == '\b') {
        if (cmd_idx > 0) {
          cmd_idx--;
          putchar('\b');
        }
      } else if (c >= 32 && c <= 126 && cmd_idx < 62) {
        cmd_buf[cmd_idx++] = c;
        putchar(c);
      }
    }
    taskYIELD();
  }
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================
 */
int main(void) {
  while (*KEY_STAT & 1)
    (void)*KEY_DATA;

  *PAGE_REG = 0;
  term_clear();
  init_filesystem();

  xTaskCreate(vTaskShell, "Shell", 1024, NULL, 1, NULL);
  vTaskStartScheduler();

  while (1)
    ;
  return 0;
}