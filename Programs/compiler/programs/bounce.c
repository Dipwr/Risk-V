#include <stdint.h>

// Mapped as 32-bit words per pixel!
#define GRAPHIC_RAM ((volatile uint32_t *)0x00080000)
#define PAGE_REG ((volatile uint32_t *)0x000A0000)
#define KEY_STAT ((volatile uint32_t *)0x000A0024)

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 100
#define BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT) // 16,000 32-bit words
#define SQUARE_SIZE 5

// 32-bit word color values
#define COLOR_WHITE 0x0000FFFF
#define COLOR_BLACK 0x00008000

// Draw/erase 8x8 region in 32-bit Graphic RAM
void draw_square_page(int page, int x, int y, uint32_t color) {
  // Offset in 32-bit words
  int page_offset = page * BUFFER_SIZE;

  for (int row = 0; row < SQUARE_SIZE; row++) {
    int current_y = y + row;
    if (current_y < 0 || current_y >= SCREEN_HEIGHT)
      continue;

    int row_offset = page_offset + (current_y * SCREEN_WIDTH);

    for (int col = 0; col < SQUARE_SIZE; col++) {
      int current_x = x + col;
      if (current_x < 0 || current_x >= SCREEN_WIDTH)
        continue;

      GRAPHIC_RAM[row_offset + current_x] = color;
    }
  }
}

// Clear a 32-bit buffer page
void clear_buffer_page(int page, uint32_t color) {
  int page_offset = page * BUFFER_SIZE;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    GRAPHIC_RAM[page_offset + i] = color;
  }
}

int main(void) {
  int x = 10, y = 10;
  int dx = 1, dy = 1;

  // Keep separate history for each 32-bit buffer
  int old_x[2] = {10, 10};
  int old_y[2] = {10, 10};

  uint32_t active_page = 0;

  // 1. Clear both 32-bit framebuffers
  clear_buffer_page(0, COLOR_WHITE);
  clear_buffer_page(1, COLOR_WHITE);
  *PAGE_REG = 0;

  while (1) {
    // Exit if key pressed
    if (*KEY_STAT & 0x1) {
      break;
    }

    // 2. Select back buffer
    uint32_t back_page = active_page ^ 1;

    // 3. Erase previous square on back buffer
    draw_square_page(back_page, old_x[back_page], old_y[back_page],
                     COLOR_WHITE);

    // 4. Draw new square position on back buffer
    draw_square_page(back_page, x, y, COLOR_BLACK);

    // Store history for this buffer
    old_x[back_page] = x;
    old_y[back_page] = y;

    // 5. Physics update
    x += dx;
    y += dy;

    if (x <= 0 || x >= (SCREEN_WIDTH - SQUARE_SIZE)) {
      dx = -dx;
      x += dx;
    }
    if (y <= 0 || y >= (SCREEN_HEIGHT - SQUARE_SIZE)) {
      dy = -dy;
      y += dy;
    }

    // 6. Flip page
    active_page = back_page;
    *PAGE_REG = active_page;
  }

  // Reset screen back to Buffer 0
  *PAGE_REG = 0;
  clear_buffer_page(0, COLOR_WHITE);
  return 0;
}