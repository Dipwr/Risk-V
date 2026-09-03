#include "Vmain_cpu.h"
#include <atomic>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <verilated.h>

#if __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

// ============================================================================
// FRAMEBUFFER & DISPLAY CONFIGURATION (320x200, 16-Bit RGB565 Color)
// ============================================================================
#define FB_WIDTH 320
#define FB_HEIGHT 200
#define DISPLAY_SCALE 3
#define SCREEN_WIDTH (FB_WIDTH * DISPLAY_SCALE)   // 960 px
#define SCREEN_HEIGHT (FB_HEIGHT * DISPLAY_SCALE) // 600 px
#define PANEL_HEIGHT 70                           // Bottom UI Panel
#define WINDOW_WIDTH SCREEN_WIDTH
#define WINDOW_HEIGHT (SCREEN_HEIGHT + PANEL_HEIGHT) // 670 px

#define PIXELS_PER_PAGE (FB_WIDTH * FB_HEIGHT)
#define PAGE_SIZE_BYTES (PIXELS_PER_PAGE * 2)

#define VRAM_BASE_ADDR 0x00082000
#define VRAM_END_ADDR (VRAM_BASE_ADDR + (PAGE_SIZE_BYTES * 2))

constexpr uint32_t CYCLES_PER_BATCH = 300000;

alignas(16) uint8_t gr_ram[PAGE_SIZE_BYTES * 2] = {0};

// Thread-safe state communication
std::atomic<bool> sim_running{true};
std::atomic<bool> sim_reset_requested{false};
std::atomic<bool> vram_dirty{true};
std::atomic<uint32_t> active_display_page{0};
std::atomic<uint64_t> global_cycle_count{0};
std::atomic<double> g_last_mhz{0.0};

// Mouse MMIO Atomic States
std::atomic<uint32_t> g_mouse_x{0};
std::atomic<uint32_t> g_mouse_y{0};
std::atomic<uint32_t> g_mouse_btn{0};

// Thread-safe keyboard queue
static std::queue<uint8_t> key_queue;
static std::mutex key_mutex;

static inline void push_key(uint8_t k) {
  std::lock_guard<std::mutex> lock(key_mutex);
  key_queue.push(k);
}

static inline uint8_t pop_key() {
  std::lock_guard<std::mutex> lock(key_mutex);
  if (key_queue.empty())
    return 0;
  uint8_t k = key_queue.front();
  key_queue.pop();
  return k;
}

static inline bool has_key() {
  std::lock_guard<std::mutex> lock(key_mutex);
  return !key_queue.empty();
}

static inline void clear_keys() {
  std::lock_guard<std::mutex> lock(key_mutex);
  while (!key_queue.empty())
    key_queue.pop();
}

static inline size_t get_key_count() {
  std::lock_guard<std::mutex> lock(key_mutex);
  return key_queue.size();
}

double sc_time_stamp() {
  return static_cast<double>(
      global_cycle_count.load(std::memory_order_relaxed));
}

// ============================================================================
// OFFICIAL IBM VGA 8x8 BITMAP FONT
// ============================================================================
static const uint8_t font8x8_basic[95][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ' ' (32)
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // '!'
    {0x36, 0x36, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00}, // '"'
    {0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00}, // '#'
    {0x18, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x18, 0x00}, // '$'
    {0x00, 0x63, 0x66, 0x0C, 0x18, 0x33, 0x63, 0x00}, // '%'
    {0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00}, // '&'
    {0x30, 0x30, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00}, // '\''
    {0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00}, // '('
    {0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00}, // ')'
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // '*'
    {0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00}, // '+'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30}, // ','
    {0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00}, // '-'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, // '.'
    {0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, // '/'
    {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00}, // '0' (48)
    {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00}, // '1'
    {0x3C, 0x66, 0x06, 0x0C, 0x18, 0x30, 0x7E, 0x00}, // '2'
    {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00}, // '3'
    {0x0C, 0x1C, 0x3C, 0x6C, 0xFE, 0x0C, 0x0C, 0x00}, // '4'
    {0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00}, // '5'
    {0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00}, // '6'
    {0x7E, 0x66, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x00}, // '7'
    {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00}, // '8'
    {0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00}, // '9'
    {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00}, // ':'
    {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 0x00}, // ';'
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // '<'
    {0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00}, // '='
    {0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00}, // '>'
    {0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00}, // '?'
    {0x3C, 0x66, 0x6E, 0x6E, 0x60, 0x3E, 0x00, 0x00}, // '@'
    {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, // 'A' (65)
    {0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00}, // 'B'
    {0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}, // 'C'
    {0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00}, // 'D'
    {0xFE, 0x60, 0x60, 0x7C, 0x60, 0x60, 0xFE, 0x00}, // 'E'
    {0xFE, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00}, // 'F'
    {0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3E, 0x00}, // 'G'
    {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // 'H'
    {0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00}, // 'I'
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C, 0x00}, // 'J'
    {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}, // 'K'
    {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xFE, 0x00}, // 'L'
    {0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x00}, // 'M'
    {0x66, 0x76, 0x7E, 0x6E, 0x66, 0x66, 0x66, 0x00}, // 'N'
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // 'O'
    {0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}, // 'P'
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x0E, 0x00}, // 'Q'
    {0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x00}, // 'R'
    {0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00}, // 'S'
    {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // 'T'
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // 'U'
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // 'V'
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x36, 0x00}, // 'W'
    {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00}, // 'X'
    {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}, // 'Y'
    {0xFE, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xFE, 0x00}, // 'Z'
    {0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00}, // '['
    {0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00}, // '\'
    {0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00}, // ']'
    {0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00}, // '^'
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // '_'
    {0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00}, // '`'
    {0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00}, // 'a' (97)
    {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x7C, 0x00}, // 'b'
    {0x00, 0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 0x00}, // 'c'
    {0x06, 0x06, 0x3E, 0x66, 0x66, 0x66, 0x3E, 0x00}, // 'd'
    {0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00}, // 'e'
    {0x1C, 0x30, 0x7C, 0x30, 0x30, 0x30, 0x30, 0x00}, // 'f'
    {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x3C}, // 'g'
    {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00}, // 'h'
    {0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x3C, 0x00}, // 'i'
    {0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0x38}, // 'j'
    {0x60, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0x00}, // 'k'
    {0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // 'l'
    {0x00, 0x00, 0x6C, 0xFE, 0xD6, 0xC6, 0xC6, 0x00}, // 'm'
    {0x00, 0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00}, // 'n'
    {0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00}, // 'o'
    {0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60}, // 'p'
    {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x06}, // 'q'
    {0x00, 0x00, 0x7C, 0x66, 0x60, 0x60, 0x60, 0x00}, // 'r'
    {0x00, 0x00, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x00}, // 's'
    {0x18, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x0E, 0x00}, // 't'
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00}, // 'u'
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // 'v'
    {0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00}, // 'w'
    {0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00}, // 'x'
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x3C}, // 'y'
    {0x00, 0x00, 0x7E, 0x0C, 0x18, 0x30, 0x7E, 0x00}, // 'z'
    {0x0E, 0x18, 0x18, 0x70, 0x18, 0x18, 0x0E, 0x00}, // '{'
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // '|'
    {0x70, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x70, 0x00}, // '}'
    {0x3A, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // '~' (126)
};

void render_text_batched(SDL_Renderer *renderer, const std::string &text, int x,
                         int y, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  std::vector<SDL_Point> pts;
  pts.reserve(text.length() * 32);

  int cur_x = x;
  for (char c : text) {
    if (c >= ' ' && c <= '~') {
      const uint8_t *glyph = font8x8_basic[c - ' '];
      for (int row = 0; row < 8; ++row) {
        uint8_t g = glyph[row];
        if (!g)
          continue;
        for (int col = 0; col < 8; ++col) {
          if (g & (1 << (7 - col))) {
            pts.push_back({cur_x + col, y + row});
          }
        }
      }
    }
    cur_x += 8;
  }

  if (!pts.empty()) {
    SDL_RenderDrawPoints(renderer, pts.data(), static_cast<int>(pts.size()));
  }
}

void paste_clipboard() {
  if (SDL_HasClipboardText()) {
    char *text = SDL_GetClipboardText();
    if (text) {
      size_t count = 0;
      for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (c == '\n') {
          push_key('\r');
        } else if (c == '\r') {
          continue;
        } else {
          push_key(static_cast<uint8_t>(c));
        }
        count++;
      }
      std::cout << "\n[SIM GUI] Injected " << count
                << " characters into key buffer." << std::endl;
      SDL_free(text);
    }
  }
}

// ============================================================================
// DEDICATED HIGH-SPEED CPU SIMULATION WORKER THREAD
// ============================================================================
void cpu_simulation_worker(int argc, char **argv) {
  auto contextp = std::make_unique<VerilatedContext>();
  contextp->commandArgs(argc, argv);
  auto top = std::make_unique<Vmain_cpu>(contextp.get());

  top->CLK = 0;
  top->eval();

  uint64_t local_cycles = 0;
  uint64_t cycles_this_sec = 0;
  auto stats_start = std::chrono::steady_clock::now();

  while (sim_running.load(std::memory_order_relaxed)) {
    if (sim_reset_requested.load(std::memory_order_relaxed)) {
      clear_keys();
      local_cycles = 0;
      global_cycle_count.store(0, std::memory_order_relaxed);
      active_display_page.store(0, std::memory_order_relaxed);
      std::memset(gr_ram, 0, sizeof(gr_ram));
      vram_dirty.store(true, std::memory_order_relaxed);

      top.reset();
      contextp = std::make_unique<VerilatedContext>();
      contextp->commandArgs(argc, argv);
      contextp->time(0);
      top = std::make_unique<Vmain_cpu>(contextp.get());
      top->CLK = 0;
      top->eval();

      stats_start = std::chrono::steady_clock::now();
      cycles_this_sec = 0;

      sim_reset_requested.store(false, std::memory_order_relaxed);
      std::cout << "\n[SIM GUI] CPU Hard Reset executed." << std::endl;
    }

    Vmain_cpu *const core = top.get();

    for (uint32_t tick = 0; tick < CYCLES_PER_BATCH; ++tick) {
      // 1. Clock High
      core->CLK = 1;
      core->eval();

      // 2. Hardware MMIO Writes
      uint8_t we_mask = core->WeIO & 0x0F;
      if (we_mask != 0) [[unlikely]] {
        uint32_t addr = core->AddIO;
        uint32_t vram_offset = addr - VRAM_BASE_ADDR;

        if (vram_offset < (PAGE_SIZE_BYTES * 2)) {
          vram_dirty.store(true, std::memory_order_relaxed);
          uint32_t offset = vram_offset & ~3u;
          uint32_t wdata = core->DwIO;

          if (we_mask == 0xF) {
            *reinterpret_cast<uint32_t *>(&gr_ram[offset]) = wdata;
          } else if (we_mask == 0x3) {
            *reinterpret_cast<uint16_t *>(&gr_ram[offset]) =
                static_cast<uint16_t>(wdata);
          } else if (we_mask == 0xC) {
            *reinterpret_cast<uint16_t *>(&gr_ram[offset + 2]) =
                static_cast<uint16_t>(wdata >> 16);
          } else {
            if (we_mask & 0x1)
              gr_ram[offset] = static_cast<uint8_t>(wdata);
            if (we_mask & 0x2)
              gr_ram[offset + 1] = static_cast<uint8_t>(wdata >> 8);
            if (we_mask & 0x4)
              gr_ram[offset + 2] = static_cast<uint8_t>(wdata >> 16);
            if (we_mask & 0x8)
              gr_ram[offset + 3] = static_cast<uint8_t>(wdata >> 24);
          }
        } else if ((addr & ~3u) == 0x00080000) {
          if (we_mask & 0x01) {
            active_display_page.store(core->DwIO & 0x01,
                                      std::memory_order_relaxed);
            vram_dirty.store(true, std::memory_order_relaxed);
          }
        } else if ((addr & ~3u) == 0x00080004) {
          uint32_t byte_lane = addr & 3;
          if (we_mask & (1 << byte_lane)) {
            char c = static_cast<char>((core->DwIO >> (byte_lane * 8)) & 0xFF);
            std::cout.put(c);
            std::cout.flush();
          }
        }
      }

      // 3. Hardware MMIO Reads (Keyboard + MOUSE MMIO)
      if (core->ReIO) [[unlikely]] {
        uint32_t addr = core->AddIO & ~3u;
        if (addr == 0x00080020) {
          core->DrIO = pop_key();
        } else if (addr == 0x00080024) {
          core->DrIO = has_key() ? 1 : 0;
        } else if (addr == 0x00080028) { // MOUSE X (0..319)
          core->DrIO = g_mouse_x.load(std::memory_order_relaxed);
        } else if (addr == 0x0008002C) { // MOUSE Y (0..199)
          core->DrIO = g_mouse_y.load(std::memory_order_relaxed);
        } else if (addr == 0x00080030) { // MOUSE BUTTONS
          core->DrIO = g_mouse_btn.load(std::memory_order_relaxed);
        } else {
          core->DrIO = 0;
        }
      }

      // 4. Clock Low
      core->CLK = 0;
      core->eval();
    }

    local_cycles += CYCLES_PER_BATCH;
    cycles_this_sec += CYCLES_PER_BATCH;
    global_cycle_count.store(local_cycles, std::memory_order_relaxed);

    auto now = std::chrono::steady_clock::now();
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - stats_start)
            .count();
    if (elapsed_ms >= 500) [[unlikely]] {
      double mhz = (static_cast<double>(cycles_this_sec) /
                    static_cast<double>(elapsed_ms)) /
                   1000.0;
      g_last_mhz.store(mhz, std::memory_order_relaxed);
      stats_start = now;
      cycles_this_sec = 0;
    }
  }
}

// ============================================================================
// MAIN THREAD: GUI & SDL EVENT DISPATCH
// ============================================================================
int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "RV32IM CPU Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565,
                        SDL_TEXTUREACCESS_STREAMING, FB_WIDTH, FB_HEIGHT);

  SDL_StartTextInput();

  bool paste_mode = false;
  SDL_Rect btn_reset = {15, 615, 95, 40};
  SDL_Rect btn_mode = {120, 615, 230, 40};
  SDL_Rect btn_paste = {360, 615, 95, 40};

  std::thread cpu_thread(cpu_simulation_worker, argc, argv);

  uint32_t fps_last_time = SDL_GetTicks();
  uint32_t frames_this_sec = 0;
  double last_fps = 0.0;

  while (sim_running.load(std::memory_order_relaxed)) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        sim_running.store(false, std::memory_order_relaxed);
      }
      // Mouse Motion inside the Framebuffer area
      else if (event.type == SDL_MOUSEMOTION) {
        int mx = event.motion.x / DISPLAY_SCALE;
        int my = event.motion.y / DISPLAY_SCALE;
        if (mx >= 0 && mx < FB_WIDTH)
          g_mouse_x.store(mx, std::memory_order_relaxed);
        if (my >= 0 && my < FB_HEIGHT)
          g_mouse_y.store(my, std::memory_order_relaxed);
      }
      // Mouse Button Pressed
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mx = event.button.x;
        int my = event.button.y;

        // Control Panel Clicks
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (mx >= btn_reset.x && mx <= (btn_reset.x + btn_reset.w) &&
              my >= btn_reset.y && my <= (btn_reset.y + btn_reset.h)) {
            sim_reset_requested.store(true, std::memory_order_relaxed);
          } else if (mx >= btn_mode.x && mx <= (btn_mode.x + btn_mode.w) &&
                     my >= btn_mode.y && my <= (btn_mode.y + btn_mode.h)) {
            paste_mode = !paste_mode;
          } else if (mx >= btn_paste.x && mx <= (btn_paste.x + btn_paste.w) &&
                     my >= btn_paste.y && my <= (btn_paste.y + btn_paste.h)) {
            paste_clipboard();
          }
          // Inside Screen
          if (my < SCREEN_HEIGHT) {
            g_mouse_btn.fetch_or(1,
                                 std::memory_order_relaxed); // Set bit 0 (Left)
          }
        }
      }
      // Mouse Button Released
      else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          g_mouse_btn.fetch_and(~1, std::memory_order_relaxed); // Clear bit 0
        }
      }
      // Keyboard input
      else if (event.type == SDL_TEXTINPUT) {
        for (int i = 0; event.text.text[i] != '\0'; i++) {
          push_key(static_cast<uint8_t>(event.text.text[i]));
        }
      } else if (event.type == SDL_KEYDOWN) {
        Uint16 mod = event.key.keysym.mod;
        SDL_Keycode sym = event.key.keysym.sym;

        if (paste_mode && sym == SDLK_v && (mod & (KMOD_CTRL | KMOD_GUI))) {
          paste_clipboard();
        } else if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER) {
          push_key('\r');
        } else if (sym == SDLK_ESCAPE) {
          push_key(27);
        } else if (sym == SDLK_BACKSPACE) {
          push_key('\b');
        }
      }
    }

    if (vram_dirty.load(std::memory_order_relaxed)) {
      uint32_t page_byte_offset =
          active_display_page.load(std::memory_order_relaxed) * PAGE_SIZE_BYTES;
      const uint16_t *vram_16 =
          reinterpret_cast<const uint16_t *>(&gr_ram[page_byte_offset]);
      SDL_UpdateTexture(texture, NULL, vram_16, FB_WIDTH * sizeof(uint16_t));
      vram_dirty.store(false, std::memory_order_relaxed);
    }

    SDL_Rect display_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &display_rect);

    SDL_Rect panel_rect = {0, SCREEN_HEIGHT, SCREEN_WIDTH, PANEL_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, &panel_rect);

    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetRenderDrawColor(renderer, 160, 40, 40, 255);
    SDL_RenderFillRect(renderer, &btn_reset);
    render_text_batched(renderer, "RESET CPU", btn_reset.x + 11,
                        btn_reset.y + 16, {255, 255, 255, 255});

    if (paste_mode) {
      SDL_SetRenderDrawColor(renderer, 180, 110, 20, 255);
      SDL_RenderFillRect(renderer, &btn_mode);
      render_text_batched(renderer, "MODE: PASTE (Ctrl+V)", btn_mode.x + 35,
                          btn_mode.y + 16, {255, 255, 255, 255});
    } else {
      SDL_SetRenderDrawColor(renderer, 30, 90, 150, 255);
      SDL_RenderFillRect(renderer, &btn_mode);
      render_text_batched(renderer, "MODE: NORMAL (Direct)", btn_mode.x + 31,
                          btn_mode.y + 16, {255, 255, 255, 255});
    }

    SDL_SetRenderDrawColor(renderer, 40, 140, 60, 255);
    SDL_RenderFillRect(renderer, &btn_paste);
    render_text_batched(renderer, "PASTE NOW", btn_paste.x + 11,
                        btn_paste.y + 16, {255, 255, 255, 255});

    char buf_mhz[32], buf_fps[32], buf_cycles[48], buf_queue[32];
    snprintf(buf_mhz, sizeof(buf_mhz), "Speed:  %.2f MHz",
             g_last_mhz.load(std::memory_order_relaxed));
    snprintf(buf_fps, sizeof(buf_fps), "FPS:    %.1f", last_fps);
    snprintf(
        buf_cycles, sizeof(buf_cycles), "Cycles: %llu",
        (unsigned long long)global_cycle_count.load(std::memory_order_relaxed));
    snprintf(buf_queue, sizeof(buf_queue), "Buffer: %zu keys", get_key_count());

    render_text_batched(renderer, buf_mhz, 470, SCREEN_HEIGHT + 15,
                        {220, 220, 220, 255});
    render_text_batched(renderer, buf_fps, 470, SCREEN_HEIGHT + 40,
                        {220, 220, 220, 255});
    render_text_batched(renderer, buf_cycles, 700, SCREEN_HEIGHT + 15,
                        {180, 220, 255, 255});
    render_text_batched(renderer, buf_queue, 700, SCREEN_HEIGHT + 40,
                        {255, 220, 180, 255});

    SDL_RenderPresent(renderer);
    frames_this_sec++;

    uint32_t now = SDL_GetTicks();
    if (now - fps_last_time >= 1000) {
      last_fps = static_cast<double>(frames_this_sec) * 1000.0 /
                 static_cast<double>(now - fps_last_time);
      fps_last_time = now;
      frames_this_sec = 0;
    }

    SDL_Delay(16);
  }

  if (cpu_thread.joinable()) {
    cpu_thread.join();
  }

  SDL_StopTextInput();
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}