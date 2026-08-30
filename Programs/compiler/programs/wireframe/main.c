/* ============================================================================
 * RV32I BARE-METAL 3D WIREFRAME MODEL RENDERER (RGB565 UPDATED)
 * ============================================================================
 */

#include <stdint.h>

// Hardware MMIO Base Addresses
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

#define COLOR_WHITE ((uint16_t)0xFFFF)
#define COLOR_BLACK ((uint16_t)0x0000)

struct Vec3 {
  int x, y, z;
};
struct Vec2 {
  int x, y;
};

#include "model_data.h"

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

void clear_buffer_page(int page, uint16_t color) {
  int page_offset = page * PAGE_PIXELS;
  for (int i = 0; i < PAGE_PIXELS; i++) {
    GRAPHIC_RAM[page_offset + i] = color;
  }
}

void draw_line(int page, int x0, int y0, int x1, int y1, uint16_t color) {
  int dx = iabs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -iabs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx + dy, e2;
  int page_offset = page * PAGE_PIXELS;

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

      // Center projection mapped to 320x200 (160, 100)
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