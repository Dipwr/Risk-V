/* ============================================================================
 * RV32IM REALISTIC WORKLOAD PROFILER & BENCHMARK
 * ============================================================================
 * Target: Custom RV32IM Core (Bare-Metal)
 * Load Address: 0x00040000 | Stack: 0x0007FFF0
 *
 * This program serves as a realistic workload for Profile-Guided Optimization
 * (PGO) and simulator profiling:
 *  - 3D Fixed-Point Matrix Rotation & Perspective Projection (heavy MUL, SRA,
 * ADD)
 *  - Integer Bresenham 3D Wireframe Rasterization
 *  - Double-Buffered RGB565 Framebuffer Page Flipping (PAGE_REG 0x00080000)
 *  - Procedural Plasma/Texture Generation (Division, Modulo, Bitwise Logic)
 * ============================================================================
 */

#include <stdint.h>

#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define COLOR_BLACK ((uint16_t)0x0000)
#define COLOR_WHITE ((uint16_t)0xFFFF)
#define COLOR_CYAN ((uint16_t)0x07FF)
#define COLOR_YELLOW ((uint16_t)0xFFE0)
#define COLOR_MAGENTA ((uint16_t)0xF81F)

/* --- 16-BIT FIXED-POINT MATH (8.8 FIXED POINT) --- */
#define FP_SHIFT 8
#define FP_ONE (1 << FP_SHIFT)
#define INT_TO_FP(x) ((x) << FP_SHIFT)
#define FP_TO_INT(x) ((x) >> FP_SHIFT)
#define FP_MUL(a, b) (((a) * (b)) >> FP_SHIFT)
#define FP_DIV(a, b) (((a) << FP_SHIFT) / (b))

/* Fast Integer Sine Table (256 entries = 360 degrees, 8.8 fixed point: -256 to
 * +256) */
static const int16_t sin_table[256] = {
    0,    6,    12,   18,   25,   31,   37,   43,   49,   56,   62,   68,
    74,   80,   86,   92,   97,   103,  109,  115,  120,  126,  131,  136,
    142,  147,  152,  157,  162,  167,  171,  176,  180,  185,  189,  193,
    197,  201,  205,  208,  212,  215,  219,  222,  225,  228,  231,  233,
    236,  238,  240,  242,  244,  246,  247,  249,  250,  251,  252,  253,
    254,  254,  255,  255,  255,  255,  255,  254,  254,  253,  252,  251,
    250,  249,  247,  246,  244,  242,  240,  238,  236,  233,  231,  228,
    225,  222,  219,  215,  212,  208,  205,  201,  197,  193,  189,  185,
    180,  176,  171,  167,  162,  157,  152,  147,  142,  136,  131,  126,
    120,  115,  109,  103,  97,   92,   86,   80,   74,   68,   62,   56,
    49,   43,   37,   31,   25,   18,   12,   6,    0,    -6,   -12,  -18,
    -25,  -31,  -37,  -43,  -49,  -56,  -62,  -68,  -74,  -80,  -86,  -92,
    -97,  -103, -109, -115, -120, -126, -131, -136, -142, -147, -152, -157,
    -162, -167, -171, -176, -180, -185, -189, -193, -197, -201, -205, -208,
    -212, -215, -219, -222, -225, -228, -231, -233, -236, -238, -240, -242,
    -244, -246, -247, -249, -250, -251, -252, -253, -254, -254, -255, -255,
    -255, -255, -255, -254, -254, -253, -252, -251, -250, -249, -247, -246,
    -244, -242, -240, -238, -236, -233, -231, -228, -225, -222, -219, -215,
    -212, -208, -205, -201, -197, -193, -189, -185, -180, -176, -171, -167,
    -162, -157, -152, -147, -142, -136, -131, -126, -120, -115, -109, -103,
    -97,  -92,  -86,  -80,  -74,  -68,  -62,  -56,  -49,  -43,  -37,  -31,
    -25,  -18,  -12,  -6};

static inline int16_t fp_sin(uint8_t angle) { return sin_table[angle]; }

static inline int16_t fp_cos(uint8_t angle) {
  return sin_table[(uint8_t)(angle + 64)];
}

/* --- 3D MESH DEFINITION (Cube with 8 vertices, 12 edges) --- */
typedef struct {
  int x, y, z;
} Vec3;
typedef struct {
  int u, v;
} Edge;

static const Vec3 cube_verts[8] = {
    {-40, -40, -40}, {40, -40, -40}, {40, 40, -40}, {-40, 40, -40},
    {-40, -40, 40},  {40, -40, 40},  {40, 40, 40},  {-40, 40, 40}};

static const Edge cube_edges[12] = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
                                    {4, 5}, {5, 6}, {6, 7}, {7, 4},
                                    {0, 4}, {1, 5}, {2, 6}, {3, 7}};

/* --- FAST GRAPHICS ROUTINES --- */
static inline int iabs(int v) { return (v < 0) ? -v : v; }

static inline void put_pixel(int page, int x, int y, uint16_t color) {
  if ((uint32_t)x < SCREEN_WIDTH && (uint32_t)y < SCREEN_HEIGHT) {
    GRAPHIC_RAM[(page * PAGE_PIXELS) + (y * SCREEN_WIDTH) + x] = color;
  }
}

void clear_page(int page, uint16_t color) {
  uint32_t offset = page * PAGE_PIXELS;
  uint32_t c32 = (uint32_t)color | ((uint32_t)color << 16);
  volatile uint32_t *p32 = (volatile uint32_t *)&GRAPHIC_RAM[offset];
  for (int i = 0; i < PAGE_PIXELS / 2; i++) {
    p32[i] = c32;
  }
}

void draw_line(int page, int x0, int y0, int x1, int y1, uint16_t color) {
  int dx = iabs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -iabs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx + dy;
  int e2;

  while (1) {
    put_pixel(page, x0, y0, color);
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

/* Background generator: exercises math/modulo pipeline */
void render_procedural_background(int page, uint8_t time) {
  uint32_t offset = page * PAGE_PIXELS;
  for (int y = 0; y < SCREEN_HEIGHT; y += 4) {
    for (int x = 0; x < SCREEN_WIDTH; x += 4) {
      uint8_t val = (uint8_t)((x ^ y) + time);
      uint16_t col = MAKE_RGB(val >> 3, (val >> 2) & 0x1F, (x + y) >> 4);

      // Fill 4x4 block
      for (int dy = 0; dy < 4; dy++) {
        for (int dx = 0; dx < 4; dx++) {
          GRAPHIC_RAM[offset + ((y + dy) * SCREEN_WIDTH) + (x + dx)] = col;
        }
      }
    }
  }
}

/* --- MASTER BENCHMARK / PROFILER LOOP --- */
int main(void) {
  uint32_t active_page = 0;
  uint8_t angle_x = 0;
  uint8_t angle_y = 0;
  uint8_t angle_z = 0;

  // Profiling frame limit (run 1000 full frames, or until keypress)
  const uint32_t TOTAL_FRAMES = 100000;

  for (uint32_t frame = 0; frame < TOTAL_FRAMES; frame++) {
    uint32_t back_page = active_page ^ 1;

    // 1. Procedural background compute & memory sweep
    render_procedural_background(back_page, (uint8_t)frame);

    // 2. Fixed-point Trigonometric Matrix Transform (RV32M MUL heavy)
    int16_t sin_x = fp_sin(angle_x), cos_x = fp_cos(angle_x);
    int16_t sin_y = fp_sin(angle_y), cos_y = fp_cos(angle_y);
    int16_t sin_z = fp_sin(angle_z), cos_z = fp_cos(angle_z);

    int proj_x[8], proj_y[8];

    for (int i = 0; i < 8; i++) {
      int x = cube_verts[i].x;
      int y = cube_verts[i].y;
      int z = cube_verts[i].z;

      // Rotate Y
      int x1 = (x * cos_y + z * sin_y) >> FP_SHIFT;
      int z1 = (-x * sin_y + z * cos_y) >> FP_SHIFT;

      // Rotate X
      int y2 = (y * cos_x - z1 * sin_x) >> FP_SHIFT;
      int z2 = (y * sin_x + z1 * cos_x) >> FP_SHIFT;

      // Rotate Z
      int x3 = (x1 * cos_z - y2 * sin_z) >> FP_SHIFT;
      int y3 = (x1 * sin_z + y2 * cos_z) >> FP_SHIFT;

      // Perspective Projection (RV32M DIV)
      int z_dist = z2 + 180;
      if (z_dist < 1)
        z_dist = 1;

      proj_x[i] = 160 + ((x3 * 220) / z_dist);
      proj_y[i] = 100 + ((y3 * 220) / z_dist);
    }

    // 3. Rasterize 3D Wireframe Edges
    for (int e = 0; e < 12; e++) {
      int u = cube_edges[e].u;
      int v = cube_edges[e].v;
      draw_line(back_page, proj_x[u], proj_y[u], proj_x[v], proj_y[v],
                COLOR_WHITE);
    }

    // 4. Hardware Page Flip via MMIO
    *PAGE_REG = back_page;
    active_page = back_page;

    angle_x += 2;
    angle_y += 3;
    angle_z += 1;

    if (*KEY_STAT & 0x1)
      break;
  }

  // Return to Wozmon ROM
  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
  return 0;
}