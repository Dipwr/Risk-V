#include "Vmain_cpu.h"
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <verilated.h>

#if __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

// Framebuffer dimensions (320x200)
#define FB_WIDTH 320
#define FB_HEIGHT 200
#define PAGE_SIZE_WORDS (FB_WIDTH * FB_HEIGHT) // 64,000 words per page (256 KB)

// 128,000 32-bit words total (512 KB total for Page 0 + Page 1)
uint32_t gr_ram[PAGE_SIZE_WORDS * 2] = {0};
uint32_t active_display_page = 0;
std::queue<uint8_t> key_buffer;

const uint32_t base_colors[10] = {
    0xFFFFFFFF, 0xFF000000, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF,
    0xFFFFFF00, 0xFF00FFFF, 0xFFFF00FF, 0xFFFF8000, 0xFFFFC0CB};

uint32_t decode_digital_color(uint16_t val) {
  if (val & 0x8000) {
    uint8_t r = (val >> 10) & 0x1F;
    uint8_t g = (val >> 5) & 0x1F;
    uint8_t b = val & 0x1F;
    return 0xFF000000 | ((r << 3) | (r >> 2)) << 16 |
           ((g << 3) | (g >> 2)) << 8 | ((b << 3) | (b >> 2));
  }
  if (val < 10)
    return base_colors[val];
  if (val >= 32 && val <= 63) {
    uint8_t gray = (val - 32) * 255 / 31;
    return 0xFF000000 | (gray << 16) | (gray << 8) | gray;
  }
  if (val >= 64 && val <= 127) {
    uint8_t r = ((val >> 4) & 0x03) * 85;
    uint8_t g = ((val >> 2) & 0x03) * 85;
    uint8_t b = (val & 0x03) * 85;
    return 0xFF000000 | (r << 16) | (g << 8) | b;
  }
  return 0xFF000000;
}

// Color Lookup Table to avoid recalculating colors per pixel per frame
static uint32_t color_lut[65536];

// Gate host-side checks behind a bitmask to avoid per-cycle syscall overhead
static constexpr vluint64_t HOST_CHECK_INTERVAL = 8192; // Must be power of 2
static constexpr vluint64_t HOST_CHECK_MASK = HOST_CHECK_INTERVAL - 1;

// Legacy timestamp function required by Verilator when linking with -flto
double sc_time_stamp() { return 0; }

int main(int argc, char **argv) {
  VerilatedContext *contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);
  contextp->randReset(0);

  Vmain_cpu *top = new Vmain_cpu{contextp};

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return 1;

  // Detect native host display refresh rate
  SDL_DisplayMode display_mode;
  int target_fps = 60; // Default fallback
  if (SDL_GetCurrentDisplayMode(0, &display_mode) == 0 &&
      display_mode.refresh_rate > 0) {
    target_fps = display_mode.refresh_rate;
  }
  std::cout << "[SYSTEM] Detected Host Display Refresh Rate: " << target_fps
            << " Hz" << std::endl;

  // Scale window 3x (960x600 window size)
  SDL_Window *window = SDL_CreateWindow(
      "Visual Wozmon Display (320x200)", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, FB_WIDTH * 3, FB_HEIGHT * 3, SDL_WINDOW_SHOWN);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, FB_WIDTH, FB_HEIGHT);

  SDL_StartTextInput();

  // Populate the color LUT once at startup
  for (uint32_t i = 0; i < 65536; ++i) {
    color_lut[i] = decode_digital_color(static_cast<uint16_t>(i));
  }

  top->CLK = 0;
  top->eval();

  bool running = true;
  vluint64_t main_time = 0;

  // High-precision sub-millisecond frame pacing counters
  const uint64_t perf_freq = SDL_GetPerformanceFrequency();
  uint64_t last_frame_counter = SDL_GetPerformanceCounter();
  const double frame_delay_seconds = 1.0 / static_cast<double>(target_fps);

  // --- Statistics Counters ---
  uint32_t stats_last_time = SDL_GetTicks();
  vluint64_t cycles_this_second = 0;
  uint32_t frames_this_second = 0;

  while (!contextp->gotFinish() && running) {

    // ----------------------------------------------------
    // 1. CLOCK LOW PHASE (Combinational setup)
    // ----------------------------------------------------
    top->CLK = 0;
    top->eval();

    uint32_t addr = top->AddIO;
    bool re = top->ReIO;
    bool we = top->WeIO;
    uint32_t wdata = top->DwIO;

    bool pop_pending = false;

    // ----------------------------------------------------
    // 2. APPLY ASYNCHRONOUS READS (8 KB MMIO at 0x00080000)
    // ----------------------------------------------------
    if (re) {
      if (addr >= 0x00080020 && addr <= 0x00080023) {
        top->DrIO =
            key_buffer.empty() ? 0 : static_cast<uint32_t>(key_buffer.front());
        pop_pending = true;
      } else if (addr >= 0x00080024 && addr <= 0x00080027) {
        top->DrIO = key_buffer.empty() ? 0 : 1;
      } else {
        top->DrIO = 0;
      }
      top->eval();
    }

    // ----------------------------------------------------
    // 3. CLOCK RISING EDGE (Latch state & Pop)
    // ----------------------------------------------------
    top->CLK = 1;
    top->eval();

    if (pop_pending && !key_buffer.empty()) {
      key_buffer.pop();
    }

    if (we) {
      // MMIO Controls (0x00080000 - 0x00081FFF)
      if (addr >= 0x00080000 && addr <= 0x00080003) {
        active_display_page = wdata & 0x1;
      } else if (addr >= 0x00080004 && addr <= 0x00080007) {
        std::putchar(static_cast<char>(wdata & 0xFF));
        std::fflush(stdout);
      }
      // Graphics RAM starting after 8 KB MMIO block (0x00082000)
      else if (addr >= 0x00082000 &&
               addr < (0x00082000 + (PAGE_SIZE_WORDS * 2 * 4))) {
        uint32_t word_idx = (addr - 0x00082000) >> 2;
        gr_ram[word_idx] = wdata;
      }
    }

    // ----------------------------------------------------
    // 4. HOST-SIDE WORK: Gated to bounded wall-clock checks
    // ----------------------------------------------------
    if ((main_time & HOST_CHECK_MASK) == 0) {
      uint64_t current_counter = SDL_GetPerformanceCounter();
      double elapsed_seconds =
          static_cast<double>(current_counter - last_frame_counter) /
          static_cast<double>(perf_freq);

      // ---- Native Hz render & OS event pump ----
      if (elapsed_seconds >= frame_delay_seconds) {
        last_frame_counter = current_counter;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            running = false;
          } else if (event.type == SDL_TEXTINPUT) {
            uint8_t c = static_cast<uint8_t>(event.text.text[0]);
            if (c != '\r' && c != '\n') {
              key_buffer.push(c);
            }
          } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN ||
                event.key.keysym.sym == SDLK_KP_ENTER) {
              key_buffer.push(0x0D);
            } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
              key_buffer.push('\b');
            } else if (event.key.keysym.sym == SDLK_ESCAPE) {
              key_buffer.push(27);
            }
          }
        }

        uint32_t pixels[FB_WIDTH * FB_HEIGHT];
        uint32_t page_word_offset = active_display_page * PAGE_SIZE_WORDS;

        for (int i = 0; i < FB_WIDTH * FB_HEIGHT; i++) {
          pixels[i] = color_lut[gr_ram[page_word_offset + i] & 0xFFFF];
        }

        SDL_UpdateTexture(texture, NULL, pixels, FB_WIDTH * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        frames_this_second++;
      }

      // ---- Performance metrics reporting ----
      uint32_t current_time = SDL_GetTicks();
      uint32_t elapsed_ms = current_time - stats_last_time;
      if (elapsed_ms >= 1000) {
        double mhz = (double)cycles_this_second / (elapsed_ms * 1000.0);
        double fps = (double)frames_this_second * 1000.0 / elapsed_ms;

        std::cout << "\r[CPU METRICS] Speed: " << mhz
                  << " MHz | Refresh: " << fps
                  << " FPS | Total Cycles: " << main_time << std::flush;

        stats_last_time = current_time;
        cycles_this_second = 0;
        frames_this_second = 0;
      }
    }

    cycles_this_second++;
    main_time++;
  }

  std::cout << std::endl;
  SDL_StopTextInput();
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  delete top;
  delete contextp;
  return 0;
}