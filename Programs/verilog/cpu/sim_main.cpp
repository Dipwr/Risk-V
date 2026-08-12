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

// ============================================================================
// FRAMEBUFFER CONFIGURATION (320x200, 16-Bit RGB565 Color)
// ============================================================================
#define FB_WIDTH	320
#define FB_HEIGHT	200
#define PIXELS_PER_PAGE	(FB_WIDTH * FB_HEIGHT)
#define PAGE_SIZE_BYTES	(PIXELS_PER_PAGE * 2)

#define VRAM_BASE_ADDR	0x00082000
#define VRAM_END_ADDR	(VRAM_BASE_ADDR + (PAGE_SIZE_BYTES * 2))

uint8_t gr_ram[PAGE_SIZE_BYTES * 2] = {0};
uint32_t active_display_page = 0;
std::queue<uint8_t> key_buffer;

// Framebuffer pixel staging array moved to static memory
static uint32_t render_pixels[FB_WIDTH * FB_HEIGHT];
static uint32_t color_lut[65536];

// Decode Standard 16-bit RGB565 to 32-bit ARGB8888
inline uint32_t decode_rgb565(uint16_t val) {
	uint8_t r = (val >> 11) & 0x1F;
	uint8_t g = (val >> 5)  & 0x3F;
	uint8_t b =  val        & 0x1F;

	uint8_t r8 = (r << 3) | (r >> 2);
	uint8_t g8 = (g << 2) | (g >> 4);
	uint8_t b8 = (b << 3) | (b >> 2);

	return 0xFF000000 | (r8 << 16) | (g8 << 8) | b8;
}

vluint64_t main_time = 0;

double sc_time_stamp() {
	return main_time;
}

int main(int argc, char** argv) {
	Verilated::commandArgs(argc, argv);
	auto top = std::make_unique<Vmain_cpu>();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("RV32I CPU Simulator (16-Bit RGB565 Color)",
										  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  FB_WIDTH * 3, FB_HEIGHT * 3, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
											 SDL_TEXTUREACCESS_STREAMING, FB_WIDTH, FB_HEIGHT);

	SDL_StartTextInput();

	for (uint32_t i = 0; i < 65536; ++i) {
		color_lut[i] = decode_rgb565(static_cast<uint16_t>(i));
	}

	top->CLK = 0;
	top->eval();

	uint32_t stats_last_time = SDL_GetTicks();
	uint32_t render_last_time = SDL_GetTicks();
	uint32_t cycles_this_second = 0;
	uint32_t frames_this_second = 0;

	while (!Verilated::gotFinish()) {
		// --- 1. Clock High Transition ---
		top->CLK = 1;
		top->eval();
		main_time++;
		cycles_this_second++;

		// --- 2. Clean Hardware Byte-Lane Write Handling ---
		uint8_t we_mask = top->WeIO & 0x0F;
		if (we_mask != 0) [[unlikely]] {
			uint32_t addr  = top->AddIO;
			uint32_t wdata = top->DwIO;

			if (addr >= VRAM_BASE_ADDR && addr < VRAM_END_ADDR) {
				const uint32_t offset = (addr & ~3u) - VRAM_BASE_ADDR;
				switch (we_mask) {
				case 0x1: gr_ram[offset]     = static_cast<uint8_t>(wdata);       break;
				case 0x2: gr_ram[offset + 1] = static_cast<uint8_t>(wdata >> 8);  break;
				case 0x4: gr_ram[offset + 2] = static_cast<uint8_t>(wdata >> 16); break;
				case 0x8: gr_ram[offset + 3] = static_cast<uint8_t>(wdata >> 24); break;
				case 0x3:
					gr_ram[offset]     = static_cast<uint8_t>(wdata);
					gr_ram[offset + 1] = static_cast<uint8_t>(wdata >> 8);
					break;
				case 0x6:
					gr_ram[offset + 1] = static_cast<uint8_t>(wdata >> 8);
					gr_ram[offset + 2] = static_cast<uint8_t>(wdata >> 16);
					break;
				case 0xC:
					gr_ram[offset + 2] = static_cast<uint8_t>(wdata >> 16);
					gr_ram[offset + 3] = static_cast<uint8_t>(wdata >> 24);
					break;
				case 0xF:
					gr_ram[offset]     = static_cast<uint8_t>(wdata);
					gr_ram[offset + 1] = static_cast<uint8_t>(wdata >> 8);
					gr_ram[offset + 2] = static_cast<uint8_t>(wdata >> 16);
					gr_ram[offset + 3] = static_cast<uint8_t>(wdata >> 24);
					break;
				default:
					for (unsigned lane = 0; lane < 4; ++lane)
						if (we_mask & (1u << lane))
							gr_ram[offset + lane] = static_cast<uint8_t>(wdata >> (8u * lane));
				}
			}
			else if ((addr & ~3u) == 0x00080000) {
				if (we_mask & 0x01) {
					active_display_page = wdata & 0x01;
				}
			}
		}

		// --- 3. Handle Keyboard MMIO Reads ---
		if (top->ReIO) [[unlikely]] {
			uint32_t addr = top->AddIO;
			if ((addr & ~3u) == 0x00080020) {
				if (!key_buffer.empty()) {
					top->DrIO = key_buffer.front();
					key_buffer.pop();
				} else {
					top->DrIO = 0;
				}
			} else if ((addr & ~3u) == 0x00080024) {
				top->DrIO = key_buffer.empty() ? 0 : 1;
			} else {
				top->DrIO = 0;
			}
		}

		// --- 4. Clock Low Transition ---
		top->CLK = 0;
		top->eval();

		// --- 5. Poll Events every 8192 cycles (& 0x1FFF), Render at 60 FPS (~16ms) ---
		if ((main_time & 0x1FFFF) == 0) [[unlikely]] {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					goto cleanup;
				} else if (event.type == SDL_TEXTINPUT) {
					for (int i = 0; event.text.text[i] != '\0'; i++) {
						key_buffer.push(static_cast<uint8_t>(event.text.text[i]));
					}
				} else if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
						key_buffer.push('\r');
					} else if (event.key.keysym.sym == SDLK_ESCAPE) {
						key_buffer.push(27);
					} else if (event.key.keysym.sym == SDLK_BACKSPACE) {
						key_buffer.push('\b');
					}
				}
			}

			uint32_t now = SDL_GetTicks();
			if (now - render_last_time >= 16) {
				render_last_time = now;

				uint32_t page_byte_offset = active_display_page * PAGE_SIZE_BYTES;
				const uint16_t* vram_16 = reinterpret_cast<const uint16_t*>(&gr_ram[page_byte_offset]);

				for (int i = 0; i < FB_WIDTH * FB_HEIGHT; i++) {
					render_pixels[i] = color_lut[vram_16[i]];
				}

				SDL_UpdateTexture(texture, NULL, render_pixels, FB_WIDTH * sizeof(uint32_t));
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, NULL, NULL);
				SDL_RenderPresent(renderer);

				frames_this_second++;
			}

			// Statistics do not need a host timer call on every simulated cycle.
			const uint32_t elapsed_ms = now - stats_last_time;
			if (elapsed_ms >= 1000) [[unlikely]] {
				const double mhz = static_cast<double>(cycles_this_second) /
				                   (static_cast<double>(elapsed_ms) * 1000.0);
				const double fps = static_cast<double>(frames_this_second) * 1000.0 /
				                   static_cast<double>(elapsed_ms);
				std::cout << "\r[CPU METRICS] Speed: " << mhz
				          << " MHz | Refresh: " << fps
				          << " FPS | Total Cycles: " << main_time << std::flush;
				stats_last_time = now;
				cycles_this_second = 0;
				frames_this_second = 0;
			}
		}

	}

cleanup:
	SDL_StopTextInput();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}