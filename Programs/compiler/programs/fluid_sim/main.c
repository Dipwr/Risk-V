/* ============================================================================
 * 2D EULERIAN WIND TUNNEL - TOP-TO-BOTTOM OPTIMIZED CFD SOLVER
 * ============================================================================
 * Target: Custom RV32IM Core (Bare-Metal)
 * Load Address: 0x00040000 | Stack: 0x0007FFF0
 *
 * Updates:
 *  - Top-to-Bottom Forward Incompressibility Sweep (Natural Downstream
 * Propagation)
 *  - Stride-1 Pointer-Increment Optimization in Gauss-Seidel Inner Loop
 *  - 100% Pure Navier-Stokes Physics (Zero synthetic pulses)
 *  - Interactive Obstacle Size ([O]/[L]), Smoke Pos ([W]/[S]) & Thickness
 * ([T]/[G])
 *  - Solid Deep Navy Blue Obstacles & On-Screen HUD / Help Overlay ([H])
 * ============================================================================
 */

#include <stdint.h>

/* --- MMIO HARDWARE REGISTERS --- */
#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)
#define GRAPHIC_RAM ((volatile uint16_t *)0x00082000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT)

/* --- GRID CONFIGURATION --- */
#define GW 80
#define GH 50
#define CELL_SCALE 4 // 80 * 4 = 320, 50 * 4 = 200
#define NUM_CELLS (GW * GH)

#define IDX(x, y) (((y) * GW) + (x))

/* --- 10.6 FIXED-POINT CONFIGURATION --- */
#define FP_SHIFT 6
#define FP_ONE (1 << FP_SHIFT) // 64 = 1.0 cell/frame
#define OVER_RELAXATION 118    // 1.84 in fixed point (fast convergence)

/* --- RGB565 PALETTE GENERATION --- */
#define MAKE_RGB(r, g, b)                                                      \
  ((uint16_t)((((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F)))

#define COLOR_WHITE ((uint16_t)0xFFFF)
#define COLOR_BLACK ((uint16_t)0x0000)
#define COLOR_NAVY_DARK ((uint16_t)0x010B)  // Pure Deep Navy Blue (#00205B)
#define COLOR_HUD_BG ((uint16_t)0x18C3)     // Dark Charcoal Overlay
#define COLOR_HUD_BORDER ((uint16_t)0x037F) // Cyan Accent Border
#define COLOR_YELLOW ((uint16_t)0xFFE0)
#define COLOR_CYAN ((uint16_t)0x07FF)

/* --- SIMULATION STATE BUFFERS --- */
static int16_t u[NUM_CELLS]; // Horizontal velocity
static int16_t v[NUM_CELLS]; // Vertical velocity
static int16_t new_u[NUM_CELLS];
static int16_t new_v[NUM_CELLS];

static int16_t smoke[NUM_CELLS]; // Smoke concentration
static int16_t new_smoke[NUM_CELLS];
static int16_t pressure[NUM_CELLS]; // Pressure field

static uint8_t is_solid[NUM_CELLS]; // Obstacle/Wall mask

/* Runtime Tunable Parameters */
static int32_t g_inflow_speed = 140; // ~2.18 cells/frame
static int g_pressure_iters = 14;    // Gauss-Seidel relaxation iterations
static int g_view_mode = 0; // 0 = Black Smoke on White, 1 = Pressure Heatmap
static int g_show_help = 0; // 1 = Show Help Overlay

static int g_obstacle_radius = 6; // Radius of cylinder in grid cells (2..16)
static int g_smoke_y = 24;        // Smoke stream center Y-position
static int g_smoke_thickness = 1; // Smoke half-thickness (1 = 3 cells wide)

/* ============================================================================
 * EMBEDDED 5x7 BITMAP FONT ENGINE
 * ============================================================================
 */
static const uint8_t font5x7[95][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // ' ' (32)
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // '!'
    {0x00, 0x07, 0x00, 0x07, 0x00}, // '"'
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // '#'
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // '$'
    {0x23, 0x13, 0x08, 0x64, 0x62}, // '%'
    {0x36, 0x49, 0x55, 0x22, 0x50}, // '&'
    {0x00, 0x05, 0x03, 0x00, 0x00}, // '\''
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // '('
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // ')'
    {0x14, 0x08, 0x3E, 0x08, 0x14}, // '*'
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // '+'
    {0x00, 0x50, 0x30, 0x00, 0x00}, // ','
    {0x08, 0x08, 0x08, 0x08, 0x08}, // '-'
    {0x00, 0x60, 0x60, 0x00, 0x00}, // '.'
    {0x20, 0x10, 0x08, 0x04, 0x02}, // '/'
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // '0' (48)
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // '1'
    {0x42, 0x61, 0x51, 0x49, 0x46}, // '2'
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // '3'
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // '4'
    {0x27, 0x45, 0x45, 0x45, 0x39}, // '5'
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // '6'
    {0x01, 0x71, 0x09, 0x05, 0x03}, // '7'
    {0x36, 0x49, 0x49, 0x49, 0x36}, // '8'
    {0x06, 0x49, 0x49, 0x29, 0x1E}, // '9'
    {0x00, 0x36, 0x36, 0x00, 0x00}, // ':'
    {0x00, 0x56, 0x36, 0x00, 0x00}, // ';'
    {0x08, 0x14, 0x22, 0x41, 0x00}, // '<'
    {0x14, 0x14, 0x14, 0x14, 0x14}, // '='
    {0x00, 0x41, 0x22, 0x14, 0x08}, // '>'
    {0x02, 0x01, 0x51, 0x09, 0x06}, // '?'
    {0x32, 0x49, 0x79, 0x41, 0x3E}, // '@'
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, // 'A' (65)
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // 'B'
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // 'C'
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, // 'D'
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // 'E'
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // 'F'
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, // 'G'
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 'H'
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // 'I'
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // 'J'
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // 'K'
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // 'L'
    {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // 'M'
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // 'N'
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 'O'
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // 'P'
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 'Q'
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // 'R'
    {0x46, 0x49, 0x49, 0x49, 0x31}, // 'S'
    {0x01, 0x01, 0x7F, 0x01, 0x01}, // 'T'
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 'U'
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 'V'
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // 'W'
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 'X'
    {0x07, 0x08, 0x70, 0x08, 0x07}, // 'Y'
    {0x61, 0x51, 0x49, 0x45, 0x43}, // 'Z'
    {0x00, 0x7F, 0x41, 0x41, 0x00}, // '['
    {0x02, 0x04, 0x08, 0x10, 0x20}, // '\'
    {0x00, 0x41, 0x41, 0x7F, 0x00}, // ']'
    {0x04, 0x02, 0x01, 0x02, 0x04}, // '^'
    {0x40, 0x40, 0x40, 0x40, 0x40}, // '_'
    {0x00, 0x01, 0x02, 0x04, 0x00}, // '`'
    {0x20, 0x54, 0x54, 0x54, 0x78}, // 'a' (97)
    {0x7F, 0x48, 0x44, 0x44, 0x38}, // 'b'
    {0x38, 0x44, 0x44, 0x44, 0x20}, // 'c'
    {0x38, 0x44, 0x44, 0x48, 0x7F}, // 'd'
    {0x38, 0x54, 0x54, 0x54, 0x18}, // 'e'
    {0x08, 0x7E, 0x09, 0x01, 0x02}, // 'f'
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, // 'g'
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // 'h'
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // 'i'
    {0x20, 0x40, 0x44, 0x3D, 0x00}, // 'j'
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // 'k'
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // 'l'
    {0x7C, 0x04, 0x18, 0x04, 0x78}, // 'm'
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // 'n'
    {0x38, 0x44, 0x44, 0x44, 0x38}, // 'o'
    {0x7C, 0x14, 0x14, 0x14, 0x08}, // 'p'
    {0x08, 0x14, 0x14, 0x18, 0x7C}, // 'q'
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // 'r'
    {0x48, 0x54, 0x54, 0x54, 0x20}, // 's'
    {0x04, 0x3F, 0x44, 0x40, 0x20}, // 't'
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // 'u'
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // 'v'
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // 'w'
    {0x44, 0x28, 0x10, 0x28, 0x44}, // 'x'
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, // 'y'
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // 'z'
    {0x00, 0x08, 0x36, 0x41, 0x00}, // '{'
    {0x00, 0x00, 0x7F, 0x00, 0x00}, // '|'
    {0x00, 0x41, 0x36, 0x08, 0x00}, // '}'
    {0x08, 0x08, 0x2A, 0x1C, 0x08}  // '~'
};

static inline void put_pixel(int page, int x, int y, uint16_t color) {
  if ((uint32_t)x < SCREEN_WIDTH && (uint32_t)y < SCREEN_HEIGHT) {
    GRAPHIC_RAM[(page * PAGE_PIXELS) + (y * SCREEN_WIDTH) + x] = color;
  }
}

static void fill_rect(int page, int x, int y, int w, int h, uint16_t color) {
  uint32_t page_offset = page * PAGE_PIXELS;
  for (int j = 0; j < h; j++) {
    int py = y + j;
    if (py < 0 || py >= SCREEN_HEIGHT)
      continue;
    for (int i = 0; i < w; i++) {
      int px = x + i;
      if (px < 0 || px >= SCREEN_WIDTH)
        continue;
      GRAPHIC_RAM[page_offset + (py * SCREEN_WIDTH) + px] = color;
    }
  }
}

static void draw_char(int page, char c, int x, int y, uint16_t color) {
  if (c < 32 || c > 126)
    return;
  const uint8_t *glyph = font5x7[c - 32];
  for (int col = 0; col < 5; col++) {
    uint8_t line = glyph[col];
    for (int row = 0; row < 7; row++) {
      if (line & (1 << row)) {
        put_pixel(page, x + col, y + row, color);
      }
    }
  }
}

static void draw_text(int page, const char *str, int x, int y, uint16_t color) {
  int cur_x = x;
  while (*str) {
    draw_char(page, *str++, cur_x, y, color);
    cur_x += 6;
  }
}

/* ============================================================================
 * TERMINAL I/O HELPERS
 * ============================================================================
 */
static void print_string(const char *str) {
  while (*str)
    *TERM_OUT = (uint32_t)(*str++);
}

static void print_dec(uint32_t val) {
  char buf[12];
  int i = 0;
  if (val == 0) {
    *TERM_OUT = (uint32_t)'0';
    return;
  }
  while (val > 0) {
    buf[i++] = (val % 10) + '0';
    val /= 10;
  }
  while (i > 0) {
    *TERM_OUT = (uint32_t)buf[--i];
  }
}

static inline int is_key_available(void) { return (*KEY_STAT & 0x1); }

static inline char read_keyboard(void) {
  if (is_key_available())
    return (char)(*KEY_DATA);
  return 0;
}

static void clear_page(int page, uint16_t color) {
  uint32_t offset = page * PAGE_PIXELS;
  uint32_t c32 = (uint32_t)color | ((uint32_t)color << 16);
  volatile uint32_t *p32 = (volatile uint32_t *)&GRAPHIC_RAM[offset];
  for (int i = 0; i < PAGE_PIXELS / 2; i++) {
    p32[i] = c32;
  }
}

/* ============================================================================
 * DYNAMIC GEOMETRY UPDATE (Symmetrical Obstacle & Boundary Walls)
 * ============================================================================
 */
void update_obstacle_geometry(void) {
  for (int y = 1; y < GH - 1; y++) {
    for (int x = 0; x < GW; x++) {
      is_solid[IDX(x, y)] = 0;
    }
  }

  // Top and Bottom Boundary Walls
  for (int x = 0; x < GW; x++) {
    is_solid[IDX(x, 0)] = 1;
    is_solid[IDX(x, GH - 1)] = 1;
  }

  // Circular Cylinder centered at x=20, y=24
  int cx = 20;
  int cy = 24;
  int r2 = g_obstacle_radius * g_obstacle_radius;

  for (int y = 1; y < GH - 1; y++) {
    for (int x = 1; x < GW - 1; x++) {
      int dx = x - cx;
      int dy = y - cy;
      if ((dx * dx + dy * dy) <= r2) {
        is_solid[IDX(x, y)] = 1;
        u[IDX(x, y)] = 0;
        v[IDX(x, y)] = 0;
        smoke[IDX(x, y)] = 0;
      }
    }
  }
}

void init_fluid_scene(void) {
  for (int i = 0; i < NUM_CELLS; i++) {
    u[i] = 0;
    v[i] = 0;
    new_u[i] = 0;
    new_v[i] = 0;
    smoke[i] = 0;
    new_smoke[i] = 0;
    pressure[i] = 0;
    is_solid[i] = 0;
  }
  update_obstacle_geometry();
}

/* ============================================================================
 * EULERIAN FLUID SOLVER (Pure Navier-Stokes)
 * ============================================================================
 */

// 1. Inflow and Clean Smoke Injection (No synthetic perturbations)
void inject_inflow(void) {
  int y_min = g_smoke_y - g_smoke_thickness;
  int y_max = g_smoke_y + g_smoke_thickness;
  if (y_min < 1)
    y_min = 1;
  if (y_max > GH - 2)
    y_max = GH - 2;

  for (int y = 1; y < GH - 1; y++) {
    u[IDX(1, y)] = g_inflow_speed;
    u[IDX(2, y)] = g_inflow_speed;
    v[IDX(1, y)] = 0;

    if (y >= y_min && y <= y_max) {
      smoke[IDX(1, y)] = FP_ONE;
      smoke[IDX(2, y)] = FP_ONE;
    }
  }
}

// 2. High-Efficiency Top-to-Bottom Incompressibility Relaxation Solver
void solve_incompressibility(void) {
  for (int i = 0; i < NUM_CELLS; i++) {
    pressure[i] = 0;
  }

  for (int iter = 0; iter < g_pressure_iters; iter++) {
    // Enforce inlet fan velocity
    for (int y = 1; y < GH - 1; y++) {
      u[IDX(1, y)] = g_inflow_speed;
    }

    // Forward Top-to-Bottom Sweep (Natural Downstream Propagation with Stride-1
    // Indexing)
    for (int y = 1; y < GH - 1; y++) {
      int idx = y * GW + 1;
      for (int x = 1; x < GW - 1; x++, idx++) {
        if (is_solid[idx])
          continue;

        int s_left = (x > 1) ? (1 - is_solid[idx - 1]) : 0;
        int s_right = 1 - is_solid[idx + 1];
        int s_bot = 1 - is_solid[idx - GW];
        int s_top = 1 - is_solid[idx + GW];
        int s_tot = s_left + s_right + s_bot + s_top;

        if (s_tot == 0)
          continue;

        int32_t div = (u[idx + 1] - u[idx]) + (v[idx + GW] - v[idx]);
        int32_t p = (-div * OVER_RELAXATION) / (s_tot * FP_ONE);

        pressure[idx] += p;

        if (s_left)
          u[idx] -= p;
        if (s_right)
          u[idx + 1] += p;
        if (s_bot)
          v[idx] -= p;
        if (s_top)
          v[idx + GW] += p;
      }
    }

    // Outflow boundary
    for (int y = 1; y < GH - 1; y++) {
      u[IDX(GW - 1, y)] = u[IDX(GW - 2, y)];
      v[IDX(GW - 1, y)] = v[IDX(GW - 2, y)];
    }
  }
}

// 3. Bilinear Sampler with Rounded Fixed-Point Shifts
static inline int16_t sample_bilinear(const int16_t *field, int fp_x,
                                      int fp_y) {
  int x0 = fp_x >> FP_SHIFT;
  int y0 = fp_y >> FP_SHIFT;

  if (x0 < 0)
    x0 = 0;
  if (x0 > GW - 2)
    x0 = GW - 2;
  if (y0 < 0)
    y0 = 0;
  if (y0 > GH - 2)
    y0 = GH - 2;

  int x1 = x0 + 1;
  int y1 = y0 + 1;

  int fx = fp_x - (x0 << FP_SHIFT);
  int fy = fp_y - (y0 << FP_SHIFT);

  if (fx < 0)
    fx = 0;
  if (fx > FP_ONE)
    fx = FP_ONE;
  if (fy < 0)
    fy = 0;
  if (fy > FP_ONE)
    fy = FP_ONE;

  int s00 = field[IDX(x0, y0)];
  int s10 = field[IDX(x1, y0)];
  int s01 = field[IDX(x0, y1)];
  int s11 = field[IDX(x1, y1)];

  int top_row = s00 + ((((s10 - s00) * fx) + (FP_ONE >> 1)) >> FP_SHIFT);
  int bot_row = s01 + ((((s11 - s01) * fx) + (FP_ONE >> 1)) >> FP_SHIFT);

  return (int16_t)(top_row +
                   ((((bot_row - top_row) * fy) + (FP_ONE >> 1)) >> FP_SHIFT));
}

// 4. Semi-Lagrangian Back-Trace Advection
void advect_fields(void) {
  // Advect U
  for (int y = 1; y < GH - 1; y++) {
    for (int x = 2; x < GW; x++) {
      int idx = IDX(x, y);
      if (is_solid[idx] || is_solid[idx - 1]) {
        new_u[idx] = 0;
        continue;
      }

      int avg_v = (v[idx - 1] + v[idx] + v[idx - 1 + GW] + v[idx + GW]) >> 2;
      int prev_x = (x << FP_SHIFT) - u[idx];
      int prev_y = (y << FP_SHIFT) - avg_v;

      new_u[idx] = sample_bilinear(u, prev_x, prev_y);
    }
  }

  // Advect V
  for (int y = 1; y < GH - 1; y++) {
    for (int x = 1; x < GW - 1; x++) {
      int idx = IDX(x, y);
      if (is_solid[idx] || is_solid[idx - GW]) {
        new_v[idx] = 0;
        continue;
      }

      int avg_u = (u[idx - GW] + u[idx + 1 - GW] + u[idx] + u[idx + 1]) >> 2;
      int prev_x = (x << FP_SHIFT) - avg_u;
      int prev_y = (y << FP_SHIFT) - v[idx];

      new_v[idx] = sample_bilinear(v, prev_x, prev_y);
    }
  }

  // Advect Smoke
  for (int y = 1; y < GH - 1; y++) {
    for (int x = 1; x < GW - 1; x++) {
      int idx = IDX(x, y);
      if (is_solid[idx]) {
        new_smoke[idx] = 0;
        continue;
      }

      int center_u = (u[idx] + u[idx + 1]) >> 1;
      int center_v = (v[idx] + v[idx + GW]) >> 1;

      int prev_x = (x << FP_SHIFT) - center_u;
      int prev_y = (y << FP_SHIFT) - center_v;

      new_smoke[idx] = sample_bilinear(smoke, prev_x, prev_y);
    }
  }

  for (int i = 0; i < NUM_CELLS; i++) {
    u[i] = new_u[i];
    v[i] = new_v[i];
    smoke[i] = new_smoke[i];
  }
}

/* ============================================================================
 * SCIENTIFIC PRESSURE JET COLORMAP
 * ============================================================================
 */
static inline uint16_t get_scientific_pressure_color(int32_t p_val) {
  int val = p_val + 32;
  if (val < 0)
    val = 0;
  if (val > 64)
    val = 64;

  int r = 0, g = 0, b = 0;
  if (val < 16) {
    r = 0;
    g = (val * 63) / 16;
    b = 31;
  } else if (val < 32) {
    r = 0;
    g = 63;
    b = 31 - (((val - 16) * 31) / 16);
  } else if (val < 48) {
    r = ((val - 32) * 31) / 16;
    g = 63;
    b = 0;
  } else {
    r = 31;
    g = 63 - (((val - 48) * 63) / 16);
    b = 0;
  }
  return MAKE_RGB(r, g, b);
}

/* ============================================================================
 * GRAPHICS RENDERING & ON-SCREEN HUD OVERLAYS
 * ============================================================================
 */
void render_fluid_frame(int page) {
  uint32_t page_offset = page * PAGE_PIXELS;

  // 1. Render Fluid Field & Solid Deep Navy Obstacles (No Highlight)
  for (int gy = 0; gy < GH; gy++) {
    int py = gy * CELL_SCALE;
    for (int gx = 0; gx < GW; gx++) {
      int px = gx * CELL_SCALE;
      int idx = IDX(gx, gy);

      uint16_t color;

      if (is_solid[idx]) {
        color = COLOR_NAVY_DARK;
      } else if (g_view_mode == 0) {
        // Mode 0: Black Smoke on White Canvas
        int s = smoke[idx];
        if (s > FP_ONE)
          s = FP_ONE;
        if (s < 0)
          s = 0;

        int r = 31 - ((s * 31) >> FP_SHIFT);
        int g = 63 - ((s * 63) >> FP_SHIFT);
        int b = 31 - ((s * 31) >> FP_SHIFT);

        color = MAKE_RGB(r, g, b);
      } else {
        // Mode 1: Scientific Pressure Heatmap
        color = get_scientific_pressure_color(pressure[idx]);
      }

      // Blit 4x4 tile into VRAM using 32-bit double-pixel writes
      uint32_t color32 = (uint32_t)color | ((uint32_t)color << 16);
      for (int dy = 0; dy < 4; dy++) {
        uint32_t row_addr = page_offset + ((py + dy) * SCREEN_WIDTH) + px;
        volatile uint32_t *p32 = (volatile uint32_t *)&GRAPHIC_RAM[row_addr];
        p32[0] = color32;
        p32[1] = color32;
      }
    }
  }

  // 2. Render Top HUD Status Bar (Height: 11px)
  fill_rect(page, 0, 0, 320, 11, COLOR_HUD_BG);

  char buf[16];
  draw_text(page, g_view_mode ? "M:PRES" : "M:SMK", 4, 2, COLOR_WHITE);

  // Iterations
  draw_text(page, "IT:", 48, 2, COLOR_CYAN);
  buf[0] = (g_pressure_iters / 10) + '0';
  buf[1] = (g_pressure_iters % 10) + '0';
  buf[2] = '\0';
  draw_text(page, buf, 66, 2, COLOR_YELLOW);

  // Wind Speed
  draw_text(page, "SP:", 84, 2, COLOR_CYAN);
  int spd_int = g_inflow_speed / FP_ONE;
  int spd_frac = ((g_inflow_speed % FP_ONE) * 10) / FP_ONE;
  buf[0] = spd_int + '0';
  buf[1] = '.';
  buf[2] = spd_frac + '0';
  buf[3] = '\0';
  draw_text(page, buf, 102, 2, COLOR_WHITE);

  // Obstacle Radius
  draw_text(page, "OBS:", 130, 2, COLOR_CYAN);
  buf[0] = (g_obstacle_radius >= 10) ? (g_obstacle_radius / 10 + '0') : ' ';
  buf[1] = (g_obstacle_radius % 10) + '0';
  buf[2] = '\0';
  draw_text(page, buf, 154, 2, COLOR_YELLOW);

  // Smoke Stream Width @ Y-Position
  draw_text(page, "SMK:", 174, 2, COLOR_CYAN);
  int smk_width = g_smoke_thickness * 2 + 1;
  buf[0] = (smk_width >= 10) ? (smk_width / 10 + '0') : (smk_width + '0');
  buf[1] = (smk_width >= 10) ? (smk_width % 10 + '0') : '@';
  buf[2] = (smk_width >= 10) ? '@' : (g_smoke_y / 10 + '0');
  buf[3] = (smk_width >= 10) ? (g_smoke_y / 10 + '0') : (g_smoke_y % 10 + '0');
  buf[4] = (smk_width >= 10) ? (g_smoke_y % 10 + '0') : '\0';
  buf[5] = '\0';
  draw_text(page, buf, 198, 2, COLOR_WHITE);

  draw_text(page, "[H]HELP", 270, 2, COLOR_YELLOW);

  // 3. Render Help Menu Overlay when Active
  if (g_show_help) {
    fill_rect(page, 30, 20, 260, 160, COLOR_HUD_BG);

    // Border
    for (int i = 0; i < 260; i++) {
      put_pixel(page, 30 + i, 20, COLOR_HUD_BORDER);
      put_pixel(page, 30 + i, 180, COLOR_HUD_BORDER);
    }
    for (int j = 0; j < 160; j++) {
      put_pixel(page, 30, 20 + j, COLOR_HUD_BORDER);
      put_pixel(page, 290, 20 + j, COLOR_HUD_BORDER);
    }

    draw_text(page, "--- WIND TUNNEL CFD CONTROLS ---", 46, 28, COLOR_CYAN);
    draw_text(page, "[V]     : TOGGLE SMOKE / PRESSURE", 42, 46, COLOR_WHITE);
    draw_text(page, "[W]/[S] : SMOKE STREAM Y-POS (UP/DN)", 42, 60,
              COLOR_WHITE);
    draw_text(page, "[T]/[G] : SMOKE THICKNESS (+/-)", 42, 74, COLOR_WHITE);
    draw_text(page, "[O]/[L] : OBSTACLE RADIUS (+/-)", 42, 88, COLOR_WHITE);
    draw_text(page, "[I]/[K] : PRESSURE ITERS (+/-2)", 42, 102, COLOR_WHITE);
    draw_text(page, "[+]/[-] : WIND TUNNEL SPEED (+/-)", 42, 116, COLOR_WHITE);
    draw_text(page, "[R]     : RESET FLUID FLOW FIELD", 42, 130, COLOR_WHITE);
    draw_text(page, "[ESC/Q] : EXIT TO WOZMON BOOTLOADER", 42, 144,
              COLOR_WHITE);
    draw_text(page, "PRESS [H] TO CLOSE OVERLAY", 78, 162, COLOR_YELLOW);
  }
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================
 */
int main(void) {
  uint32_t active_page = 0;

  print_string("=====================================================\n");
  print_string("  AERODYNAMIC WIND TUNNEL & PRESSURE FLUID SOLVER    \n");
  print_string("=====================================================\n");
  print_string("Controls:\n");
  print_string("  [V]     Toggle Smoke on White / Pressure Heatmap\n");
  print_string("  [W]/[S] Move Smoke Stream UP / DOWN\n");
  print_string("  [T]/[G] Increase / Decrease Smoke Thickness\n");
  print_string("  [O]/[L] Increase / Decrease Obstacle Radius\n");
  print_string("  [I]/[K] Increase / Decrease Pressure Iterations\n");
  print_string("  [+]/[-] Increase / Decrease Wind Speed\n");
  print_string("  [H]     Toggle On-Screen Help Menu\n");
  print_string("  [R]     Reset Simulation Field\n");
  print_string("  [ESC/Q] Exit to Wozmon ROM\n");
  print_string("=====================================================\n");

  clear_page(0, COLOR_WHITE);
  clear_page(1, COLOR_WHITE);
  *PAGE_REG = 0;

  init_fluid_scene();

  while (1) {
    uint32_t back_page = active_page ^ 1;

    // 1. Process Non-Blocking Keyboard Controls
    if (is_key_available()) {
      char key = read_keyboard();

      if (key == 'v' || key == 'V') {
        g_view_mode ^= 1;
        print_string("[CFD] Mode: ");
        print_string(g_view_mode ? "Scientific Pressure Heatmap\n"
                                 : "Black Smoke on White Canvas\n");
      } else if (key == 'h' || key == 'H') {
        g_show_help ^= 1;
      } else if (key == 'w' || key == 'W') {
        if (g_smoke_y > 3)
          g_smoke_y--;
        print_string("[CFD] Smoke Y: ");
        print_dec(g_smoke_y);
        print_string("\n");
      } else if (key == 's' || key == 'S') {
        if (g_smoke_y < GH - 4)
          g_smoke_y++;
        print_string("[CFD] Smoke Y: ");
        print_dec(g_smoke_y);
        print_string("\n");
      } else if (key == 't' || key == 'T') {
        if (g_smoke_thickness < 8)
          g_smoke_thickness++;
        print_string("[CFD] Smoke Half-Thickness: ");
        print_dec(g_smoke_thickness);
        print_string("\n");
      } else if (key == 'g' || key == 'G') {
        if (g_smoke_thickness > 0)
          g_smoke_thickness--;
        print_string("[CFD] Smoke Half-Thickness: ");
        print_dec(g_smoke_thickness);
        print_string("\n");
      } else if (key == 'o' || key == 'O') {
        if (g_obstacle_radius < 15) {
          g_obstacle_radius++;
          update_obstacle_geometry();
        }
        print_string("[CFD] Obstacle Radius: ");
        print_dec(g_obstacle_radius);
        print_string("\n");
      } else if (key == 'l' || key == 'L') {
        if (g_obstacle_radius > 2) {
          g_obstacle_radius--;
          update_obstacle_geometry();
        }
        print_string("[CFD] Obstacle Radius: ");
        print_dec(g_obstacle_radius);
        print_string("\n");
      } else if (key == 'i' || key == 'I') {
        if (g_pressure_iters < 50)
          g_pressure_iters += 2;
        print_string("[CFD] Pressure Iterations: ");
        print_dec(g_pressure_iters);
        print_string("\n");
      } else if (key == 'k' || key == 'K') {
        if (g_pressure_iters > 2)
          g_pressure_iters -= 2;
        print_string("[CFD] Pressure Iterations: ");
        print_dec(g_pressure_iters);
        print_string("\n");
      } else if (key == '+' || key == '=') {
        g_inflow_speed += 20;
        print_string("[CFD] Wind Speed Increased.\n");
      } else if (key == '-' || key == '_') {
        if (g_inflow_speed > 40)
          g_inflow_speed -= 20;
        print_string("[CFD] Wind Speed Decreased.\n");
      } else if (key == 'r' || key == 'R') {
        init_fluid_scene();
        print_string("[CFD] Fluid Field Reset.\n");
      } else if (key == 27 || key == 'q' || key == 'Q') {
        break;
      }
    }

    // 2. Navier-Stokes Physics Pipeline (Top-to-Bottom Relaxation)
    inject_inflow();
    solve_incompressibility();
    advect_fields();

    // 3. Render Graphics & HUD
    render_fluid_frame(back_page);

    // 4. Double-Buffered Frame Flip
    *PAGE_REG = back_page;
    active_page = back_page;
  }

  print_string("\nReturning to Wozmon ROM...\n");
  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();

  return 0;
}