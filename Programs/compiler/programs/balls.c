/* ============================================================================
 * RV32IM BARE-METAL MULTI-BALL PHYSICS SIMULATION (RGB565 UPDATED)
 * Target: Custom RV32IM Core (320x200 @ Double-Buffered 16-bit VRAM)
 * ============================================================================
 */

#include <stdint.h>

// ----------------------------------------------------------------------------
// 1. HARDWARE MMIO REGISTERS & VRAM MAP
// ----------------------------------------------------------------------------
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

// 16-bit Packed VRAM Pointer (1 pixel per 2 bytes)
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT) // 64,000 pixels per page

// 16-bit RGB565 Color Macro (5-bit Red, 6-bit Green, 5-bit Blue)
#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define COLOR_BLACK ((uint16_t)0x0000)
#define COLOR_WHITE MAKE_RGB(31, 63, 31)
#define COLOR_GRAY MAKE_RGB(15, 31, 15)
#define COLOR_RED MAKE_RGB(31, 0, 0)
#define COLOR_GREEN MAKE_RGB(0, 63, 0)
#define COLOR_BLUE MAKE_RGB(0, 0, 31)
#define COLOR_YELLOW MAKE_RGB(31, 63, 0)
#define COLOR_CYAN MAKE_RGB(0, 63, 31)
#define COLOR_MAGENTA MAKE_RGB(31, 0, 31)
#define COLOR_ORANGE MAKE_RGB(31, 36, 0)
#define COLOR_LIME MAKE_RGB(18, 63, 0)

int64_t __divdi3(int64_t a, int64_t b) {
  if (b == 0)
    return 0;
  int neg = (a < 0) ^ (b < 0);
  uint64_t num = (a < 0) ? -a : a;
  uint64_t den = (b < 0) ? -b : b;
  uint64_t quot = 0, rem = 0;
  for (int i = 63; i >= 0; i--) {
    rem = (rem << 1) | ((num >> i) & 1);
    if (rem >= den) {
      rem -= den;
      quot |= (1ULL << i);
    }
  }
  return neg ? -(int64_t)quot : (int64_t)quot;
}

// ----------------------------------------------------------------------------
// 2. FIXED-POINT Q16.16 ARITHMETIC & MATH FUNCTIONS
// ----------------------------------------------------------------------------
typedef int32_t fixed_t;

#define FIXED_SHIFT 16
#define INT_TO_FIXED(x) ((fixed_t)((x) << FIXED_SHIFT))
#define FIXED_TO_INT(x) ((int32_t)((x) >> FIXED_SHIFT))

static inline fixed_t fixed_mul(fixed_t a, fixed_t b) {
  return (fixed_t)(((int64_t)a * b) >> FIXED_SHIFT);
}

static inline fixed_t fixed_div(fixed_t a, fixed_t b) {
  return (fixed_t)((((int64_t)a) << FIXED_SHIFT) / b);
}

static uint32_t isqrt(uint32_t val) {
  uint32_t res = 0;
  uint32_t bit = 1u << 30;
  while (bit > val)
    bit >>= 2;
  while (bit != 0) {
    if (val >= res + bit) {
      val -= res + bit;
      res = (res >> 1) + bit;
    } else {
      res >>= 1;
    }
    bit >>= 2;
  }
  return res;
}

// ----------------------------------------------------------------------------
// 3. GRAPHICS RENDERER (16-BIT RGB565)
// ----------------------------------------------------------------------------
void clear_screen(int page, uint16_t color) {
  uint32_t offset = page * PAGE_PIXELS;
  for (uint32_t i = 0; i < PAGE_PIXELS; i++) {
    GRAPHIC_RAM[offset + i] = color;
  }
}

void draw_filled_circle(int page, int cx, int cy, int radius, uint16_t color) {
  int r2 = radius * radius;
  uint32_t page_base = page * PAGE_PIXELS;

  for (int dy = -radius; dy <= radius; dy++) {
    int py = cy + dy;
    if (py < 0 || py >= SCREEN_HEIGHT)
      continue;

    int max_x = isqrt(r2 - dy * dy);
    int start_x = cx - max_x;
    int end_x = cx + max_x;

    if (start_x < 0)
      start_x = 0;
    if (end_x >= SCREEN_WIDTH)
      end_x = SCREEN_WIDTH - 1;

    uint32_t row_offset = page_base + (py * SCREEN_WIDTH);
    for (int px = start_x; px <= end_x; px++) {
      GRAPHIC_RAM[row_offset + px] = color;
    }
  }
}

void draw_spawner_pipe(int page, int x, int y) {
  uint32_t page_base = page * PAGE_PIXELS;
  for (int py = y - 10; py <= y + 10; py++) {
    if (py < 0 || py >= SCREEN_HEIGHT)
      continue;
    uint32_t row = page_base + (py * SCREEN_WIDTH);
    for (int px = x - 5; px < SCREEN_WIDTH; px++) {
      GRAPHIC_RAM[row + px] = COLOR_GRAY;
    }
  }
}

void print_string(const char *str) {
  while (*str) {
    *TERM_OUT = (uint32_t)(*str++);
  }
}

// ----------------------------------------------------------------------------
// 4. PHYSICS ENGINE & CONTINUOUS SPAWNER LOGIC
// ----------------------------------------------------------------------------
#define MAX_BALLS 40
#define SPAWN_INTERVAL 8
#define SPAWN_X 295
#define SPAWN_Y 20

#define GRAVITY 0x00003800
#define RESTITUTION 0x0000E600
#define FRICTION 0x0000FE00

typedef struct {
  fixed_t x, y;
  fixed_t vx, vy;
  fixed_t radius;
  uint16_t color;
  int active;
} Ball;

Ball balls[MAX_BALLS];
int active_ball_count = 0;
int next_spawn_slot = 0;
uint32_t frame_counter = 0;

static const uint16_t palette[8] = {COLOR_RED,    COLOR_GREEN, COLOR_BLUE,
                                    COLOR_YELLOW, COLOR_CYAN,  COLOR_MAGENTA,
                                    COLOR_ORANGE, COLOR_LIME};

void spawn_ball(void) {
  int slot = next_spawn_slot;

  int r = 5 + (frame_counter % 4);
  balls[slot].radius = INT_TO_FIXED(r);
  balls[slot].x = INT_TO_FIXED(SPAWN_X);
  balls[slot].y = INT_TO_FIXED(SPAWN_Y);

  fixed_t launch_vx = -INT_TO_FIXED(2) - (INT_TO_FIXED(frame_counter % 3) / 2);
  fixed_t launch_vy = INT_TO_FIXED(frame_counter % 2);

  balls[slot].vx = launch_vx;
  balls[slot].vy = launch_vy;
  balls[slot].color = palette[frame_counter % 8];
  balls[slot].active = 1;

  if (active_ball_count < MAX_BALLS) {
    active_ball_count++;
  }

  next_spawn_slot = (next_spawn_slot + 1) % MAX_BALLS;
}

void init_physics(void) {
  for (int i = 0; i < MAX_BALLS; i++) {
    balls[i].active = 0;
  }
  active_ball_count = 0;
  next_spawn_slot = 0;
  frame_counter = 0;

  spawn_ball();
}

void update_physics(void) {
  fixed_t min_x = INT_TO_FIXED(0);
  fixed_t max_x = INT_TO_FIXED(SCREEN_WIDTH - 1);
  fixed_t min_y = INT_TO_FIXED(0);
  fixed_t max_y = INT_TO_FIXED(SCREEN_HEIGHT - 1);

  frame_counter++;
  if ((frame_counter % SPAWN_INTERVAL) == 0) {
    spawn_ball();
  }

  for (int i = 0; i < MAX_BALLS; i++) {
    if (!balls[i].active)
      continue;

    balls[i].vy += GRAVITY;

    balls[i].vx = fixed_mul(balls[i].vx, FRICTION);
    balls[i].vy = fixed_mul(balls[i].vy, FRICTION);

    balls[i].x += balls[i].vx;
    balls[i].y += balls[i].vy;

    if (balls[i].x - balls[i].radius < min_x) {
      balls[i].x = min_x + balls[i].radius;
      balls[i].vx = -fixed_mul(balls[i].vx, RESTITUTION);
    } else if (balls[i].x + balls[i].radius > max_x) {
      balls[i].x = max_x - balls[i].radius;
      balls[i].vx = -fixed_mul(balls[i].vx, RESTITUTION);
    }

    if (balls[i].y - balls[i].radius < min_y) {
      balls[i].y = min_y + balls[i].radius;
      balls[i].vy = -fixed_mul(balls[i].vy, RESTITUTION);
    } else if (balls[i].y + balls[i].radius > max_y) {
      balls[i].y = max_y - balls[i].radius;
      balls[i].vy = -fixed_mul(balls[i].vy, RESTITUTION);
    }
  }

  for (int i = 0; i < MAX_BALLS; i++) {
    if (!balls[i].active)
      continue;

    for (int j = i + 1; j < MAX_BALLS; j++) {
      if (!balls[j].active)
        continue;

      fixed_t dx = balls[j].x - balls[i].x;
      fixed_t dy = balls[j].y - balls[i].y;

      int32_t idx = FIXED_TO_INT(dx);
      int32_t idy = FIXED_TO_INT(dy);
      uint32_t dist_sq = (uint32_t)(idx * idx + idy * idy);

      int32_t min_dist = FIXED_TO_INT(balls[i].radius + balls[j].radius);
      uint32_t min_dist_sq = (uint32_t)(min_dist * min_dist);

      if (dist_sq < min_dist_sq && dist_sq > 0) {
        uint32_t dist = isqrt(dist_sq);
        if (dist == 0)
          continue;

        fixed_t nx = fixed_div(dx, INT_TO_FIXED(dist));
        fixed_t ny = fixed_div(dy, INT_TO_FIXED(dist));

        fixed_t kx = balls[i].vx - balls[j].vx;
        fixed_t ky = balls[i].vy - balls[j].vy;
        fixed_t p = fixed_mul(kx, nx) + fixed_mul(ky, ny);

        if (p > 0) {
          fixed_t impulse = fixed_mul(p, RESTITUTION);
          balls[i].vx -= fixed_mul(impulse, nx);
          balls[i].vy -= fixed_mul(impulse, ny);
          balls[j].vx += fixed_mul(impulse, nx);
          balls[j].vy += fixed_mul(impulse, ny);
        }

        int32_t overlap = min_dist - dist;
        fixed_t sep_x = fixed_mul(INT_TO_FIXED(overlap / 2), nx);
        fixed_t sep_y = fixed_mul(INT_TO_FIXED(overlap / 2), ny);

        balls[i].x -= sep_x;
        balls[i].y -= sep_y;
        balls[j].x += sep_x;
        balls[j].y += sep_y;
      }
    }
  }
}

// ----------------------------------------------------------------------------
// 5. MAIN APPLICATION LOOP
// ----------------------------------------------------------------------------
int main(void) {
  uint32_t active_page = 0;

  print_string(
      "[RV32IM Core] Continuous Top-Right Spawner Simulation Active...\n");

  init_physics();

  clear_screen(0, COLOR_BLACK);
  clear_screen(1, COLOR_BLACK);

  while (1) {
    if (*KEY_STAT) {
      uint32_t key = *KEY_DATA;
      (void)key;
      break;
    }

    uint32_t back_page = active_page ^ 1;

    clear_screen(back_page, COLOR_BLACK);
    update_physics();
    draw_spawner_pipe(back_page, SPAWN_X, SPAWN_Y);

    for (int i = 0; i < MAX_BALLS; i++) {
      if (!balls[i].active)
        continue;
      int cx = FIXED_TO_INT(balls[i].x);
      int cy = FIXED_TO_INT(balls[i].y);
      int r = FIXED_TO_INT(balls[i].radius);
      draw_filled_circle(back_page, cx, cy, r, balls[i].color);
    }

    *PAGE_REG = back_page;
    active_page = back_page;
  }

  print_string("[RV32IM Core] Exiting, returning control to Wozmon.\n");
  *PAGE_REG = 0;
  return 0;
}