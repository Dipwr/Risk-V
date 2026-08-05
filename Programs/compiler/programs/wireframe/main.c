#include <stdint.h>

// Hardware MMIO Base Addresses (Updated for 8 KB separation)
#define GRAPHIC_RAM ((volatile uint32_t *)0x00082000)
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

// Updated 320x200 Resolution
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT) // 64,000 words per page

#define COLOR_WHITE 0x0000FFFF
#define COLOR_BLACK 0x00008000

struct Vec3 {
  int x, y, z;
};
struct Vec2 {
  int x, y;
};

#include "model_data.h"

int __mulsi3(int a, int b) {
  int neg = (a < 0) ^ (b < 0);
  unsigned int ua = (unsigned int)(a < 0 ? -a : a);
  unsigned int ub = (unsigned int)(b < 0 ? -b : b);
  unsigned int res = 0;
  while (ub > 0) {
    if (ub & 1)
      res += ua;
    ua <<= 1;
    ub >>= 1;
  }
  return neg ? -(int)res : (int)res;
}

int __divsi3(int a, int b) {
  int neg = 0;
  unsigned int num = (unsigned int)a;
  unsigned int den = (unsigned int)b;

  if (a < 0) {
    num = (unsigned int)-a;
    neg ^= 1;
  }
  if (b < 0) {
    den = (unsigned int)-b;
    neg ^= 1;
  }
  if (den == 0)
    return 0;

  unsigned int t = num;
  int hi = 0;
  if (t & 0xFFFF0000u) {
    hi += 16;
    t >>= 16;
  }
  if (t & 0x0000FF00u) {
    hi += 8;
    t >>= 8;
  }
  if (t & 0x000000F0u) {
    hi += 4;
    t >>= 4;
  }
  if (t & 0x0000000Cu) {
    hi += 2;
    t >>= 2;
  }
  if (t & 0x00000002u) {
    hi += 1;
  }

  unsigned int quot = 0, rem = 0;
  for (int i = hi; i >= 0; i--) {
    rem <<= 1;
    rem |= (num >> i) & 1;
    if (rem >= den) {
      rem -= den;
      quot |= (1U << i);
    }
  }
  return neg ? -(int)quot : (int)quot;
}

int iabs(int v) { return (v < 0) ? -v : v; }

int16_t isin(uint8_t angle) {
  static const int16_t sin_quad[65] = {
      0,   6,   12,  18,  25,  31,  37,  43,  49,  56,  62,  68,  74,
      80,  86,  92,  97,  103, 109, 115, 120, 126, 131, 136, 142, 147,
      152, 157, 162, 167, 171, 176, 180, 185, 189, 193, 197, 201, 205,
      208, 212, 215, 219, 222, 225, 228, 231, 233, 236, 238, 240, 242,
      244, 246, 247, 249, 250, 251, 252, 253, 254, 255, 255, 256, 256};
  if (angle <= 64)
    return sin_quad[angle];
  if (angle <= 128)
    return sin_quad[128 - angle];
  if (angle <= 192)
    return -sin_quad[angle - 128];
  return -sin_quad[256 - angle];
}

int16_t icos(uint8_t angle) { return isin(angle + 64); }

void clear_buffer_page(int page, uint32_t color) {
  int page_offset = page * BUFFER_SIZE;
  for (int i = 0; i < BUFFER_SIZE; i++) {
    GRAPHIC_RAM[page_offset + i] = color;
  }
}

void draw_line(int page, int x0, int y0, int x1, int y1, uint32_t color) {
  int dx = iabs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -iabs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx + dy, e2;
  int page_offset = page * BUFFER_SIZE;

  while (1) {
    if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
      GRAPHIC_RAM[page_offset + (y0 * SCREEN_WIDTH) + x0] = color;
    }
    if (x0 == x1 && y0 == y1)
      break;

    e2 = 2 * err;
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

int main(void) {
  uint32_t active_page = 0;
  struct Vec2 proj_history[2][NUM_VERTICES];

  for (int p = 0; p < 2; p++) {
    for (int i = 0; i < NUM_VERTICES; i++) {
      proj_history[p][i].x = -1;
      proj_history[p][i].y = -1;
    }
  }

  clear_buffer_page(0, COLOR_WHITE);
  clear_buffer_page(1, COLOR_WHITE);
  *PAGE_REG = 0;

  uint8_t angle_x = 127;
  uint8_t angle_y = 0;

  while (1) {
    if (*KEY_STAT & 0x1)
      break;

    uint32_t back_page = active_page ^ 1;

    for (int i = 0; i < NUM_EDGES; i++) {
      int v0 = edges[i][0];
      int v1 = edges[i][1];
      draw_line(back_page, proj_history[back_page][v0].x,
                proj_history[back_page][v0].y, proj_history[back_page][v1].x,
                proj_history[back_page][v1].y, COLOR_WHITE);
    }

    int cx = icos(angle_x);
    int sx = isin(angle_x);
    int cy = icos(angle_y);
    int sy = isin(angle_y);

    for (int i = 0; i < NUM_VERTICES; i++) {
      int x = vertices[i].x;
      int y = vertices[i].y;
      int z = vertices[i].z;

      int x_rot1 = (x * cy - z * sy) >> 8;
      int z_rot1 = (x * sy + z * cy) >> 8;

      int y_rot2 = (y * cx - z_rot1 * sx) >> 8;
      int z_rot2 = (y * sx + z_rot1 * cx) >> 8;

      int cam_z = 250;
      int fl = 300;

      int z_depth = z_rot2 + cam_z;
      if (z_depth == 0)
        z_depth = 1;

      // Projection center mapped to 320x200 center (160, 100)
      proj_history[back_page][i].x =
          ((x_rot1 * fl) / z_depth) + (SCREEN_WIDTH / 2);
      proj_history[back_page][i].y =
          ((y_rot2 * fl) / z_depth) + (SCREEN_HEIGHT / 2);
    }

    for (int i = 0; i < NUM_EDGES; i++) {
      int v0 = edges[i][0];
      int v1 = edges[i][1];
      draw_line(back_page, proj_history[back_page][v0].x,
                proj_history[back_page][v0].y, proj_history[back_page][v1].x,
                proj_history[back_page][v1].y, COLOR_BLACK);
    }

    active_page = back_page;
    *PAGE_REG = active_page;

    angle_x += 1;
    angle_y += 2;
  }

  *PAGE_REG = 0;
  clear_buffer_page(0, COLOR_WHITE);
  return 0;
}