#include "Vmain_cpu.h"
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <verilated.h>

#if __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

// ============================================================================
// FRAMEBUFFER & DISPLAY CONFIGURATION (320x200, 16-Bit RGB565 Color)
// ============================================================================
#define FB_WIDTH        320
#define FB_HEIGHT       200
#define DISPLAY_SCALE   3
#define SCREEN_WIDTH    (FB_WIDTH * DISPLAY_SCALE)   // 960 px
#define SCREEN_HEIGHT   (FB_HEIGHT * DISPLAY_SCALE)  // 600 px
#define PANEL_HEIGHT    70                           // Bottom UI Panel
#define WINDOW_WIDTH    SCREEN_WIDTH
#define WINDOW_HEIGHT   (SCREEN_HEIGHT + PANEL_HEIGHT) // 670 px

#define PIXELS_PER_PAGE (FB_WIDTH * FB_HEIGHT)
#define PAGE_SIZE_BYTES (PIXELS_PER_PAGE * 2)

#define VRAM_BASE_ADDR  0x00082000
#define VRAM_END_ADDR   (VRAM_BASE_ADDR + (PAGE_SIZE_BYTES * 2))

// Execute 131,072 CPU cycles before pausing to check host UI/Events
constexpr uint32_t CYCLES_PER_BATCH = 131072; 

uint8_t gr_ram[PAGE_SIZE_BYTES * 2] = {0};
uint32_t active_display_page = 0;
std::queue<uint8_t> key_buffer;

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

// ============================================================================
// OFFICIAL IBM VGA 8x8 BITMAP FONT DATASET (ASCII 32..126)
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

void render_text(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	int cur_x = x;
	for (char c : text) {
		if (c >= ' ' && c <= '~') {
			const uint8_t* glyph = font8x8_basic[c - ' '];
			for (int row = 0; row < 8; ++row) {
				for (int col = 0; col < 8; ++col) {
					if (glyph[row] & (1 << (7 - col))) {
						SDL_RenderDrawPoint(renderer, cur_x + col, y + row);
					}
				}
			}
		}
		cur_x += 8;
	}
}

// Injects host OS clipboard contents into CPU key_buffer
void paste_clipboard() {
	if (SDL_HasClipboardText()) {
		char* text = SDL_GetClipboardText();
		if (text) {
			size_t count = 0;
			for (int i = 0; text[i] != '\0'; i++) {
				char c = text[i];
				if (c == '\n') {
					key_buffer.push('\r');
				} else if (c == '\r') {
					continue;
				} else {
					key_buffer.push(static_cast<uint8_t>(c));
				}
				count++;
			}
			std::cout << "\n[SIM GUI] Injected " << count << " characters into CPU key_buffer." << std::endl;
			SDL_free(text);
		}
	}
}

int main(int argc, char** argv) {
	// Explicitly manage VerilatedContext
	auto contextp = std::make_unique<VerilatedContext>();
	contextp->commandArgs(argc, argv);
	auto top = std::make_unique<Vmain_cpu>(contextp.get());

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("RV32I CPU Simulator",
										  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
											 SDL_TEXTUREACCESS_STREAMING, FB_WIDTH, FB_HEIGHT);

	SDL_StartTextInput();

	for (uint32_t i = 0; i < 65536; ++i) {
		color_lut[i] = decode_rgb565(static_cast<uint16_t>(i));
	}

	top->CLK = 0;
	top->eval();

	bool paste_mode = false;

	// UI Button Rectangles in Control Panel
	SDL_Rect btn_reset = {15, 615, 95, 40};
	SDL_Rect btn_mode  = {120, 615, 230, 40};
	SDL_Rect btn_paste = {360, 615, 95, 40};

	uint32_t stats_last_time = SDL_GetTicks();
	uint32_t render_last_time = SDL_GetTicks();
	uint32_t cycles_this_second = 0;
	uint32_t frames_this_second = 0;

	double last_mhz = 0.0;
	double last_fps = 0.0;

	while (!Verilated::gotFinish()) {
        
        // --- CORE EVALUATION LOOP (Micro-batched for speed) ---
        for (uint32_t tick = 0; tick < CYCLES_PER_BATCH; ++tick) {
            
            // --- 1. Clock High Transition ---
            top->CLK = 1;
            top->eval();

            // --- 2. Clean Hardware Byte-Lane Write Handling ---
            uint8_t we_mask = top->WeIO & 0x0F;
            if (we_mask != 0) [[unlikely]] {
                uint32_t addr  = top->AddIO;
                uint32_t vram_offset = addr - VRAM_BASE_ADDR; 
                
                // Single subtraction bounds check (underflow protects base bounds)
                if (vram_offset < (PAGE_SIZE_BYTES * 2)) {
                    uint32_t offset = vram_offset & ~3u;
                    uint32_t wdata = top->DwIO;
                    
                    if (we_mask == 0xF) {
                        std::memcpy(&gr_ram[offset], &wdata, 4);
                    } else if (we_mask == 0x3) {
                        std::memcpy(&gr_ram[offset], &wdata, 2);
                    } else if (we_mask == 0xC) {
                        uint16_t wdata_upper = static_cast<uint16_t>(wdata >> 16);
                        std::memcpy(&gr_ram[offset + 2], &wdata_upper, 2);
                    } else {
                        // Fallback for fragmented byte masks
                        if (we_mask & 0x1) gr_ram[offset]     = static_cast<uint8_t>(wdata);
                        if (we_mask & 0x2) gr_ram[offset + 1] = static_cast<uint8_t>(wdata >> 8);
                        if (we_mask & 0x4) gr_ram[offset + 2] = static_cast<uint8_t>(wdata >> 16);
                        if (we_mask & 0x8) gr_ram[offset + 3] = static_cast<uint8_t>(wdata >> 24);
                    }
                }
                else if ((addr & ~3u) == 0x00080000) {
                    if (we_mask & 0x01) {
                        active_display_page = top->DwIO & 0x01;
                    }
                }
            }

            // --- 3. Handle Keyboard MMIO Reads ---
            if (top->ReIO) [[unlikely]] {
                uint32_t addr = top->AddIO & ~3u;
                if (addr == 0x00080020) {
                    if (!key_buffer.empty()) {
                        top->DrIO = key_buffer.front();
                        key_buffer.pop();
                    } else {
                        top->DrIO = 0;
                    }
                } else if (addr == 0x00080024) {
                    top->DrIO = key_buffer.empty() ? 0 : 1;
                } else {
                    top->DrIO = 0;
                }
            }

            // --- 4. Clock Low Transition ---
            top->CLK = 0;
            top->eval();
        }

        // Advance global metrics for the batch
        main_time += CYCLES_PER_BATCH;
        cycles_this_second += CYCLES_PER_BATCH;

		// --- 5. Poll Events & Display Render ---
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto cleanup;
            } 
            // Mouse Button Clicks for Control Panel Buttons
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;

                // RESET CPU Button Clicked
                if (mx >= btn_reset.x && mx <= (btn_reset.x + btn_reset.w) &&
                    my >= btn_reset.y && my <= (btn_reset.y + btn_reset.h)) {
                    
                    // Clear keyboard queue and reset time trackers BEFORE creating new model
                    while (!key_buffer.empty()) key_buffer.pop();
                    main_time = 0;
                    active_display_page = 0;
                    std::memset(gr_ram, 0, sizeof(gr_ram));

                    // Destroy top model FIRST, then recreate context at time = 0
                    top.reset();
                    contextp = std::make_unique<VerilatedContext>();
                    contextp->commandArgs(argc, argv);
                    contextp->time(0);
                    
                    // Instantiate new model with fresh context
                    top = std::make_unique<Vmain_cpu>(contextp.get());

                    top->CLK = 0;
                    top->eval();

                    std::cout << "\n[SIM GUI] Hardware CPU state, PC, and context reset." << std::endl;
                }
                // MODE Toggle Button Clicked
                else if (mx >= btn_mode.x && mx <= (btn_mode.x + btn_mode.w) &&
                            my >= btn_mode.y && my <= (btn_mode.y + btn_mode.h)) {
                    paste_mode = !paste_mode;
                }
                // PASTE NOW Button Clicked
                else if (mx >= btn_paste.x && mx <= (btn_paste.x + btn_paste.w) &&
                            my >= btn_paste.y && my <= (btn_paste.y + btn_paste.h)) {
                    paste_clipboard();
                }
            }
            // Keyboard input processing (Passed directly to CPU)
            else if (event.type == SDL_TEXTINPUT) {
                for (int i = 0; event.text.text[i] != '\0'; i++) {
                    key_buffer.push(static_cast<uint8_t>(event.text.text[i]));
                }
            } else if (event.type == SDL_KEYDOWN) {
                Uint16 mod = event.key.keysym.mod;
                SDL_Keycode sym = event.key.keysym.sym;

                // In PASTE MODE, Ctrl+V triggers internal clipboard paste
                if (paste_mode && sym == SDLK_v && (mod & (KMOD_CTRL | KMOD_GUI))) {
                    paste_clipboard();
                }
                // Otherwise, keypresses pass directly to CPU
                else if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER) {
                    key_buffer.push('\r');
                } else if (sym == SDLK_ESCAPE) {
                    key_buffer.push(27);
                } else if (sym == SDLK_BACKSPACE) {
                    key_buffer.push('\b');
                }
            }
        }

        uint32_t now = SDL_GetTicks();
        if (now - render_last_time >= 16) {
            render_last_time = now;

            // 1. Render CPU Framebuffer
            uint32_t page_byte_offset = active_display_page * PAGE_SIZE_BYTES;
            const uint16_t* vram_16 = reinterpret_cast<const uint16_t*>(&gr_ram[page_byte_offset]);

            for (int i = 0; i < FB_WIDTH * FB_HEIGHT; i++) {
                render_pixels[i] = color_lut[vram_16[i]];
            }

            SDL_UpdateTexture(texture, NULL, render_pixels, FB_WIDTH * sizeof(uint32_t));
            
            SDL_Rect display_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &display_rect);

            // 2. Render Dedicated Control Panel (Y = 600..670)
            SDL_Rect panel_rect = {0, SCREEN_HEIGHT, SCREEN_WIDTH, PANEL_HEIGHT};
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Dark Gray Background
            SDL_RenderFillRect(renderer, &panel_rect);

            SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255); // Top Border Line
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Button 1: RESET CPU
            SDL_SetRenderDrawColor(renderer, 160, 40, 40, 255); // Red
            SDL_RenderFillRect(renderer, &btn_reset);
            render_text(renderer, "RESET CPU", btn_reset.x + 11, btn_reset.y + 16, {255, 255, 255, 255});

            // Button 2: MODE TOGGLE
            if (paste_mode) {
                SDL_SetRenderDrawColor(renderer, 180, 110, 20, 255); // Amber (Paste Mode)
                SDL_RenderFillRect(renderer, &btn_mode);
                render_text(renderer, "MODE: PASTE (Ctrl+V)", btn_mode.x + 35, btn_mode.y + 16, {255, 255, 255, 255});
            } else {
                SDL_SetRenderDrawColor(renderer, 30, 90, 150, 255); // Blue (Normal Mode)
                SDL_RenderFillRect(renderer, &btn_mode);
                render_text(renderer, "MODE: NORMAL (Direct)", btn_mode.x + 31, btn_mode.y + 16, {255, 255, 255, 255});
            }

            // Button 3: PASTE NOW
            SDL_SetRenderDrawColor(renderer, 40, 140, 60, 255); // Green
            SDL_RenderFillRect(renderer, &btn_paste);
            render_text(renderer, "PASTE NOW", btn_paste.x + 11, btn_paste.y + 16, {255, 255, 255, 255});

            // 3. Render CPU Metrics & Status
            char buf_mhz[32], buf_fps[32], buf_cycles[48], buf_queue[32];
            snprintf(buf_mhz, sizeof(buf_mhz), "Speed:  %.2f MHz", last_mhz);
            snprintf(buf_fps, sizeof(buf_fps), "FPS:    %.1f", last_fps);
            snprintf(buf_cycles, sizeof(buf_cycles), "Cycles: %llu", (unsigned long long)main_time);
            snprintf(buf_queue, sizeof(buf_queue), "Buffer: %zu keys", key_buffer.size());

            render_text(renderer, buf_mhz, 470, SCREEN_HEIGHT + 15, {220, 220, 220, 255});
            render_text(renderer, buf_fps, 470, SCREEN_HEIGHT + 40, {220, 220, 220, 255});
            render_text(renderer, buf_cycles, 700, SCREEN_HEIGHT + 15, {180, 220, 255, 255});
            render_text(renderer, buf_queue, 700, SCREEN_HEIGHT + 40, {255, 220, 180, 255});

            SDL_RenderPresent(renderer);

            frames_this_second++;
        }

        // Update CPU metrics once per second
        const uint32_t elapsed_ms = now - stats_last_time;
        if (elapsed_ms >= 1000) [[unlikely]] {
            last_mhz = static_cast<double>(cycles_this_second) / (static_cast<double>(elapsed_ms) * 1000.0);
            last_fps = static_cast<double>(frames_this_second) * 1000.0 / static_cast<double>(elapsed_ms);
            stats_last_time = now;
            cycles_this_second = 0;
            frames_this_second = 0;
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