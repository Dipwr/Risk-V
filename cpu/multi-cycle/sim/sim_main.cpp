#include "Varty_a7_top.h"
#include "Varty_a7_top___024root.h"
#include <verilated.h>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#if defined(__APPLE__)
#include <util.h>
#else
#include <pty.h>
#endif
#include <queue>
#include <sstream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>

#if __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#ifndef CPU_CLK_FREQ
#define CPU_CLK_FREQ 25000000ULL
#endif

#ifndef UART_BAUD
#define UART_BAUD 115200ULL
#endif

namespace {

constexpr int FB_WIDTH = 320;
constexpr int FB_HEIGHT = 200;
constexpr int FB_PIXELS = FB_WIDTH * FB_HEIGHT;
constexpr int DISPLAY_SCALE = 3;
constexpr int SCREEN_WIDTH = FB_WIDTH * DISPLAY_SCALE;   // 960
constexpr int SCREEN_HEIGHT = FB_HEIGHT * DISPLAY_SCALE; // 600
constexpr int PANEL_HEIGHT = 80;
constexpr int WINDOW_WIDTH = SCREEN_WIDTH;
constexpr int WINDOW_HEIGHT = SCREEN_HEIGHT + PANEL_HEIGHT;

// VESA 1280x800 @ 60 Hz CVT timing (matches vga_controller.sv)
constexpr int VGA_H_BP = 200;
constexpr int VGA_H_ACTIVE = 1280;
constexpr int VGA_V_BP = 24;
constexpr int VGA_V_ACTIVE = 800;

constexpr uint64_t CLKS_PER_BIT = CPU_CLK_FREQ / UART_BAUD;

// Exact integer picosecond half-periods for Pin-Accurate clock scheduling
constexpr uint64_t CPU_HALF_PS = 1000000000000ULL / (2ULL * CPU_CLK_FREQ);
constexpr uint64_t VGA_HALF_PS = 5991ULL; // ~83.458 MHz (11982 ps period)

enum class VgaMode { Fast = 0, Pin = 1 };

struct SimConfig {
	VgaMode vga_mode = VgaMode::Fast;
	bool headless = false;
	bool echo_stdout = true;
	uint64_t max_cycles = 0; // 0 = unlimited
	std::string boot_mem_path;
	std::string load_bin_path;
	uint32_t load_addr = 0x00010000U;
	std::string uart_link_path;
	std::string dump_ppm_path;
};

// ============================================================================
// 8x8 BITMAP FONT FOR SDL2 STATUS BAR
// ============================================================================
static const uint8_t font8x8_basic[95][8] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ' '
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
	{0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00}, // '0'
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
	{0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, // 'A'
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
	{0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00}, // '\\'
	{0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00}, // ']'
	{0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00}, // '^'
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // '_'
	{0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00}, // '`'
	{0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00}, // 'a'
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
	{0x3A, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // '~'
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
				if (!g) {
					continue;
				}
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

// ============================================================================
// SHARED SIMULATION STATE
// ============================================================================
std::atomic<bool> g_sim_running{true};
std::atomic<bool> g_reset_requested{false};
std::atomic<int> g_vga_mode{static_cast<int>(VgaMode::Fast)};
std::atomic<uint64_t> g_cpu_cycles{0};
std::atomic<uint64_t> g_vga_frames{0};
std::atomic<double> g_last_mhz{0.0};

// Shared ARGB8888 framebuffer (written by worker/snapshot, read by SDL2 thread)
std::mutex g_fb_mutex;
uint32_t g_front_fb[FB_PIXELS] = {0};
std::atomic<bool> g_fb_dirty{true};
std::atomic<bool> g_fast_snapshot_req{false};

// Host -> FPGA UART input queue (fed by PTY + SDL2 keyboard/paste)
std::mutex g_rx_mutex;
std::queue<uint8_t> g_host_to_fpga_q;
std::atomic<size_t> g_rx_queue_size{0};

void enqueue_uart_rx_byte(uint8_t b) {
	std::lock_guard<std::mutex> lock(g_rx_mutex);
	g_host_to_fpga_q.push(b);
	g_rx_queue_size.store(g_host_to_fpga_q.size(), std::memory_order_relaxed);
}

bool try_dequeue_uart_rx_byte(uint8_t &out) {
	std::lock_guard<std::mutex> lock(g_rx_mutex);
	if (g_host_to_fpga_q.empty()) {
		return false;
	}
	out = g_host_to_fpga_q.front();
	g_host_to_fpga_q.pop();
	g_rx_queue_size.store(g_host_to_fpga_q.size(), std::memory_order_relaxed);
	return true;
}

void paste_clipboard() {
	if (!SDL_HasClipboardText()) {
		return;
	}
	char *text = SDL_GetClipboardText();
	if (!text) {
		return;
	}
	size_t count = 0;
	for (int i = 0; text[i] != '\0'; ++i) {
		char c = text[i];
		if (c == '\n') {
			enqueue_uart_rx_byte('\r');
		} else if (c == '\r') {
			continue;
		} else {
			enqueue_uart_rx_byte(static_cast<uint8_t>(c));
		}
		count++;
	}
	std::cout << "\n[SIM GUI] Queued " << count << " clipboard bytes to UART RX.\n"
	          << std::flush;
	SDL_free(text);
}

// ============================================================================
// RGB565 -> VGA 4-BIT RGB444 -> ARGB8888 (MATCHES vga_controller.sv EXACTLY)
// ============================================================================
static inline uint32_t rgb444_to_argb8888(uint8_t r4, uint8_t g4, uint8_t b4) {
	uint8_t r8 = static_cast<uint8_t>((r4 << 4) | r4);
	uint8_t g8 = static_cast<uint8_t>((g4 << 4) | g4);
	uint8_t b8 = static_cast<uint8_t>((b4 << 4) | b4);
	return (0xFFU << 24) | (static_cast<uint32_t>(r8) << 16) |
	       (static_cast<uint32_t>(g8) << 8) | static_cast<uint32_t>(b8);
}

static inline uint32_t rgb565_to_vga_argb8888(uint16_t px) {
	uint8_t r4 = static_cast<uint8_t>((px >> 12) & 0xFU);
	uint8_t g4 = static_cast<uint8_t>((px >> 7) & 0xFU);
	uint8_t b4 = static_cast<uint8_t>((px >> 1) & 0xFU);
	return rgb444_to_argb8888(r4, g4, b4);
}

uint32_t g_rgb565_to_vga_lut[65536];

void init_rgb565_lut() {
	for (uint32_t px = 0; px < 65536; ++px) {
		g_rgb565_to_vga_lut[px] = rgb565_to_vga_argb8888(static_cast<uint16_t>(px));
	}
}

void write_ppm_file(const std::string &path, const uint32_t *fb) {
	std::ofstream out(path, std::ios::binary | std::ios::trunc);
	if (!out) {
		std::cerr << "[SIM] Failed to open PPM output: " << path << "\n";
		return;
	}
	out << "P6\n" << FB_WIDTH << " " << FB_HEIGHT << "\n255\n";
	std::vector<uint8_t> rgb(FB_PIXELS * 3);
	for (int i = 0; i < FB_PIXELS; ++i) {
		uint32_t p = fb[i];
		rgb[i * 3 + 0] = static_cast<uint8_t>((p >> 16) & 0xFFU);
		rgb[i * 3 + 1] = static_cast<uint8_t>((p >> 8) & 0xFFU);
		rgb[i * 3 + 2] = static_cast<uint8_t>(p & 0xFFU);
	}
	out.write(reinterpret_cast<const char *>(rgb.data()),
	          static_cast<std::streamsize>(rgb.size()));
}

// ============================================================================
// BIT-ACCURATE 8N1 UART BRIDGE + LINUX PTY
// ============================================================================
class UartBridge {
public:
	UartBridge(bool echo_stdout, std::string link_path)
		: echo_stdout_(echo_stdout), link_path_(std::move(link_path)) {}

	~UartBridge() {
		if (!link_path_.empty()) {
			unlink(link_path_.c_str());
		}
		if (slave_fd_ >= 0) {
			close(slave_fd_);
		}
		if (master_fd_ >= 0) {
			close(master_fd_);
		}
	}

	bool init() {
		char name_buf[256] = {0};
		if (openpty(&master_fd_, &slave_fd_, name_buf, nullptr, nullptr) != 0) {
			std::perror("[SIM UART] openpty failed");
			return false;
		}
		slave_path_ = name_buf;

		struct termios tio {};
		if (tcgetattr(slave_fd_, &tio) == 0) {
			cfmakeraw(&tio);
			tcsetattr(slave_fd_, TCSANOW, &tio);
		}
		if (tcgetattr(master_fd_, &tio) == 0) {
			cfmakeraw(&tio);
			tcsetattr(master_fd_, TCSANOW, &tio);
		}

		int flags = fcntl(master_fd_, F_GETFL, 0);
		if (flags >= 0) {
			fcntl(master_fd_, F_SETFL, flags | O_NONBLOCK);
		}

		if (!link_path_.empty()) {
			unlink(link_path_.c_str());
			if (symlink(slave_path_.c_str(), link_path_.c_str()) != 0) {
				std::perror("[SIM UART] symlink failed");
				return false;
			}
		}

		return true;
	}

	const std::string &slave_path() const { return slave_path_; }

	void poll_pty_input() {
		if (master_fd_ < 0) {
			return;
		}
		uint8_t buf[256];
		for (;;) {
			ssize_t n = read(master_fd_, buf, sizeof(buf));
			if (n > 0) {
				for (ssize_t i = 0; i < n; ++i) {
					enqueue_uart_rx_byte(buf[i]);
				}
			} else {
				break;
			}
		}
	}

	void reset_line_state() {
		host_tx_state_ = TxState::Idle;
		host_tx_cnt_ = 0;
		host_tx_bit_ = 0;
		host_tx_byte_ = 0;
		host_rx_pin_ = 1;

		fpga_rx_state_ = RxState::Idle;
		fpga_rx_cnt_ = 0;
		fpga_rx_bit_ = 0;
		fpga_rx_byte_ = 0;
	}

	// Returns the next value to drive onto arty_a7_top.uart_rx_pin
	inline uint8_t step_cpu_cycle(uint8_t fpga_tx_pin) {
		sample_fpga_tx(fpga_tx_pin);
		return drive_fpga_rx();
	}

	inline bool is_busy() const {
		return host_tx_state_ != TxState::Idle || fpga_rx_state_ != RxState::Idle;
	}

	uint8_t current_rx_pin() const { return host_rx_pin_; }

private:
	enum class TxState { Idle, Start, Data, Stop };
	enum class RxState { Idle, Start, Data, Stop, WaitIdle };

	uint8_t drive_fpga_rx() {
		switch (host_tx_state_) {
		case TxState::Idle:
			host_rx_pin_ = 1;
			if (g_rx_queue_size.load(std::memory_order_relaxed) != 0 &&
			    try_dequeue_uart_rx_byte(host_tx_byte_)) {
				host_tx_state_ = TxState::Start;
				host_tx_cnt_ = 0;
				host_rx_pin_ = 0;
			}
			break;

		case TxState::Start:
			host_rx_pin_ = 0;
			if (++host_tx_cnt_ >= CLKS_PER_BIT) {
				host_tx_cnt_ = 0;
				host_tx_bit_ = 0;
				host_tx_state_ = TxState::Data;
				host_rx_pin_ = (host_tx_byte_ >> 0) & 1U;
			}
			break;

		case TxState::Data:
			host_rx_pin_ = (host_tx_byte_ >> host_tx_bit_) & 1U;
			if (++host_tx_cnt_ >= CLKS_PER_BIT) {
				host_tx_cnt_ = 0;
				if (host_tx_bit_ == 7) {
					host_tx_state_ = TxState::Stop;
					host_rx_pin_ = 1;
				} else {
					host_tx_bit_++;
					host_rx_pin_ = (host_tx_byte_ >> host_tx_bit_) & 1U;
				}
			}
			break;

		case TxState::Stop:
			host_rx_pin_ = 1;
			if (++host_tx_cnt_ >= CLKS_PER_BIT) {
				host_tx_cnt_ = 0;
				host_tx_state_ = TxState::Idle;
			}
			break;
		}
		return host_rx_pin_;
	}

	void sample_fpga_tx(uint8_t pin) {
		switch (fpga_rx_state_) {
		case RxState::Idle:
			if (pin == 0) {
				fpga_rx_state_ = RxState::Start;
				fpga_rx_cnt_ = 0;
			}
			break;

		case RxState::Start:
			if (++fpga_rx_cnt_ >= (CLKS_PER_BIT / 2)) {
				fpga_rx_cnt_ = 0;
				if (pin == 0) {
					fpga_rx_bit_ = 0;
					fpga_rx_byte_ = 0;
					fpga_rx_state_ = RxState::Data;
				} else {
					fpga_rx_state_ = RxState::Idle;
				}
			}
			break;

		case RxState::Data:
			if (++fpga_rx_cnt_ >= CLKS_PER_BIT) {
				fpga_rx_cnt_ = 0;
				if (pin) {
					fpga_rx_byte_ |= static_cast<uint8_t>(1U << fpga_rx_bit_);
				}
				if (fpga_rx_bit_ == 7) {
					fpga_rx_state_ = RxState::Stop;
				} else {
					fpga_rx_bit_++;
				}
			}
			break;

		case RxState::Stop:
			if (++fpga_rx_cnt_ >= CLKS_PER_BIT) {
				fpga_rx_cnt_ = 0;
				if (pin == 1) {
					emit_byte(fpga_rx_byte_);
					fpga_rx_state_ = RxState::Idle;
				} else {
					fpga_rx_state_ = RxState::WaitIdle;
				}
			}
			break;

		case RxState::WaitIdle:
			if (pin == 1) {
				fpga_rx_state_ = RxState::Idle;
			}
			break;
		}
	}

	void emit_byte(uint8_t b) {
		if (master_fd_ >= 0) {
			ssize_t ignored = write(master_fd_, &b, 1);
			(void)ignored;
		}
		if (echo_stdout_) {
			std::putchar(b);
			if (b == '\n' || b == '\r' || b == ' ') {
				std::fflush(stdout);
			}
		}
	}

	bool echo_stdout_;
	std::string link_path_;
	std::string slave_path_;
	int master_fd_ = -1;
	int slave_fd_ = -1;

	TxState host_tx_state_ = TxState::Idle;
	uint64_t host_tx_cnt_ = 0;
	uint8_t host_tx_bit_ = 0;
	uint8_t host_tx_byte_ = 0;
	uint8_t host_rx_pin_ = 1;

	RxState fpga_rx_state_ = RxState::Idle;
	uint64_t fpga_rx_cnt_ = 0;
	uint8_t fpga_rx_bit_ = 0;
	uint8_t fpga_rx_byte_ = 0;
};

// ============================================================================
// PIN-ACCURATE VGA MONITOR (SAMPLES ONLY vga_hs, vga_vs, vga_r/g/b)
// ============================================================================
class VgaMonitor {
public:
	VgaMonitor() { reset(); }

	void reset() {
		prev_hs_ = 1;
		prev_vs_ = 0;
		hx_ = 0;
		vy_ = 0;
		in_frame_ = false;
		std::fill(std::begin(back_fb_), std::end(back_fb_), 0xFF000000U);
	}

	void on_vga_posedge(uint8_t hs, uint8_t vs, uint8_t r4, uint8_t g4,
	                    uint8_t b4) {
		// VSync falling edge marks start of vertical back porch (line 804 -> vy=0)
		if (prev_vs_ == 1 && vs == 0) {
			vy_ = 0;
			in_frame_ = true;
		}

		// VSync rising edge marks end of active frame -> commit back buffer
		if (prev_vs_ == 0 && vs == 1 && in_frame_) {
			{
				std::lock_guard<std::mutex> lock(g_fb_mutex);
				std::memcpy(g_front_fb, back_fb_, sizeof(g_front_fb));
			}
			g_fb_dirty.store(true, std::memory_order_release);
			g_vga_frames.fetch_add(1, std::memory_order_relaxed);
		}

		// HSync rising edge marks start of horizontal back porch (h_count=1480)
		if (prev_hs_ == 0 && hs == 1) {
			hx_ = 0;
			if (in_frame_) {
				vy_++;
			}
		} else {
			hx_++;
		}

		if (in_frame_ && hx_ >= VGA_H_BP && hx_ < (VGA_H_BP + VGA_H_ACTIVE) &&
		    vy_ >= VGA_V_BP && vy_ < (VGA_V_BP + VGA_V_ACTIVE)) {
			int ax = hx_ - VGA_H_BP;
			int ay = vy_ - VGA_V_BP;
			if (((ax & 3) == 0) && ((ay & 3) == 0)) {
				int fx = ax >> 2;
				int fy = ay >> 2;
				back_fb_[fy * FB_WIDTH + fx] = rgb444_to_argb8888(r4, g4, b4);
			}
		}

		prev_hs_ = hs;
		prev_vs_ = vs;
	}

private:
	uint8_t prev_hs_ = 1;
	uint8_t prev_vs_ = 0;
	int hx_ = 0;
	int vy_ = 0;
	bool in_frame_ = false;
	uint32_t back_fb_[FB_PIXELS] = {0};
};

// ============================================================================
// MEMORY PRELOAD HELPERS (OPTIONAL --boot / --load)
// ============================================================================
bool load_hex_mem_into_ram(Varty_a7_top *top, const std::string &path) {
	std::ifstream in(path);
	if (!in) {
		std::cerr << "[SIM] Cannot open boot mem file: " << path << "\n";
		return false;
	}
	auto &ram = top->rootp->arty_a7_top__DOT__u_soc_top__DOT__u_ram__DOT__mem;
	std::string line;
	size_t idx = 0;
	while (std::getline(in, line) && idx < 65536) {
		if (line.empty() || line[0] == '/' || line[0] == '#') {
			continue;
		}
		if (line[0] == '@') {
			idx = static_cast<size_t>(std::stoul(line.substr(1), nullptr, 16));
			continue;
		}
		uint32_t word = static_cast<uint32_t>(std::stoul(line, nullptr, 16));
		ram[idx++] = word;
	}
	std::cout << "[SIM] Loaded " << idx << " words from " << path << "\n";
	return true;
}

bool load_bin_into_ram(Varty_a7_top *top, const std::string &path,
                       uint32_t base_addr) {
	std::ifstream in(path, std::ios::binary);
	if (!in) {
		std::cerr << "[SIM] Cannot open binary file: " << path << "\n";
		return false;
	}
	std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
	                           std::istreambuf_iterator<char>());
	if ((base_addr & 0x3U) != 0) {
		std::cerr << "[SIM] --load-addr must be 4-byte aligned.\n";
		return false;
	}
	constexpr uint32_t RAM_BYTES = 65536U * 4U;
	if (base_addr >= RAM_BYTES || bytes.size() > (RAM_BYTES - base_addr)) {
		std::cerr << "[SIM] Binary (" << bytes.size()
		          << " B) at 0x" << std::hex << base_addr << std::dec
		          << " exceeds 256 KB system RAM.\n";
		return false;
	}

	auto &ram = top->rootp->arty_a7_top__DOT__u_soc_top__DOT__u_ram__DOT__mem;
	size_t base_word = base_addr >> 2;
	for (size_t off = 0; off < bytes.size(); off += 4) {
		uint32_t word = 0;
		for (size_t b = 0; b < 4 && (off + b) < bytes.size(); ++b) {
			word |= static_cast<uint32_t>(bytes[off + b]) << (b * 8);
		}
		ram[base_word + (off >> 2)] = word;
	}
	std::cout << "[SIM] Preloaded " << bytes.size() << " bytes from " << path
	          << " to 0x" << std::hex << base_addr << std::dec << "\n";
	return true;
}

// ============================================================================
// RESET & CLOCK PULSE HELPERS FOR arty_a7_top
// ============================================================================
void pulse_vga_cycles(Varty_a7_top *top, int count) {
	auto *root = top->rootp;
	for (int i = 0; i < count; ++i) {
		root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 1;
		top->eval();
		root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 0;
		top->eval();
	}
}

void do_board_reset(Varty_a7_top *top, UartBridge &uart, VgaMonitor &vga_mon) {
	auto *root = top->rootp;
	uart.reset_line_state();
	vga_mon.reset();

	top->uart_rx_pin = 1;
	top->btn_rst = 1;
	top->CLK100MHZ = 0;
	root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 0;
	root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 0;
	top->eval();

	// Clock CLK100MHZ enough cycles for clk_wiz_0 and clk_wiz_1 to lock, while pulsing CPU/VGA clocks
	for (int i = 0; i < 16; ++i) {
		top->CLK100MHZ = 1;
		root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 1;
		root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 1;
		top->eval();

		top->CLK100MHZ = 0;
		root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 0;
		root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 0;
		top->eval();
	}

	// Release BTN0 and propagate through 2-FF + output reset synchronizers
	top->btn_rst = 0;
	for (int i = 0; i < 8; ++i) {
		top->CLK100MHZ = 1;
		root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 1;
		root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 1;
		top->eval();

		top->CLK100MHZ = 0;
		root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 0;
		root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = 0;
		top->eval();
	}
}

void snapshot_fast_vram(Varty_a7_top *top) {
	auto *root = top->rootp;
	uint8_t page =
		root->arty_a7_top__DOT__u_soc_top__DOT__u_vga_controller__DOT__active_page & 1U;
	const auto &vram = root->arty_a7_top__DOT__u_soc_top__DOT__u_vram__DOT__mem;
	size_t base_word = static_cast<size_t>(page) * 32768U;

	uint32_t local_fb[FB_PIXELS];
	for (int i = 0; i < FB_PIXELS; i += 2) {
		uint32_t word = vram[base_word + static_cast<size_t>(i >> 1)];
		local_fb[i] = g_rgb565_to_vga_lut[word & 0xFFFFU];
		local_fb[i + 1] = g_rgb565_to_vga_lut[(word >> 16) & 0xFFFFU];
	}

	{
		std::lock_guard<std::mutex> lock(g_fb_mutex);
		std::memcpy(g_front_fb, local_fb, sizeof(g_front_fb));
	}
	g_fb_dirty.store(true, std::memory_order_release);
}

// ============================================================================
// SIMULATION WORKER THREAD
// ============================================================================
void cpu_simulation_worker(int argc, char **argv, const SimConfig &cfg,
                           UartBridge &uart) {
	init_rgb565_lut();

	auto contextp = std::make_unique<VerilatedContext>();
	contextp->commandArgs(argc, argv);

	auto top = std::make_unique<Varty_a7_top>(contextp.get(), "arty_a7_top");
	auto *root = top->rootp;

	VgaMonitor vga_mon;
	// Trigger Verilator initial blocks ($readmemh) before preloading RAM
	do_board_reset(top.get(), uart, vga_mon);

	if (!cfg.boot_mem_path.empty()) {
		if (!load_hex_mem_into_ram(top.get(), cfg.boot_mem_path)) {
			g_sim_running.store(false);
			return;
		}
	}
	if (!cfg.load_bin_path.empty()) {
		if (!load_bin_into_ram(top.get(), cfg.load_bin_path, cfg.load_addr)) {
			g_sim_running.store(false);
			return;
		}
	}
	if (!cfg.boot_mem_path.empty() || !cfg.load_bin_path.empty()) {
		do_board_reset(top.get(), uart, vga_mon);
	}

	// Fast-mode 60 Hz VBlank cadence (~16.67 ms frame, ~0.56 ms VBlank)
	constexpr uint64_t FRAME_CPU_CYCLES = CPU_CLK_FREQ / 60ULL;
	constexpr uint64_t VBLANK_CPU_CYCLES = (FRAME_CPU_CYCLES * 28ULL) / 828ULL;
	uint64_t fast_frame_cyc = 0;
	bool fast_in_vblank = false;

	// Pin-mode integer picosecond scheduler
	uint64_t sim_time_ps = 0;
	uint64_t next_cpu_edge_ps = CPU_HALF_PS;
	uint64_t next_vga_edge_ps = VGA_HALF_PS;
	uint8_t clk_cpu_val = 0;
	uint8_t clk_vga_val = 0;

	uint64_t cycle_counter = 0;
	uint64_t prev_cycles = 0;
	auto last_time = std::chrono::steady_clock::now();

	while (g_sim_running.load(std::memory_order_relaxed)) {
		if (g_reset_requested.exchange(false, std::memory_order_relaxed)) {
			do_board_reset(top.get(), uart, vga_mon);
			fast_frame_cyc = 0;
			fast_in_vblank = false;
			clk_cpu_val = 0;
			clk_vga_val = 0;
			next_cpu_edge_ps = sim_time_ps + CPU_HALF_PS;
			next_vga_edge_ps = sim_time_ps + VGA_HALF_PS;
		}

		VgaMode mode = static_cast<VgaMode>(g_vga_mode.load(std::memory_order_relaxed));

		if (mode == VgaMode::Fast) {
			// Run a batch of CPU cycles at full host speed (CLK100MHZ stays 0 once locked)
			constexpr uint64_t BATCH = 32768;
			for (uint64_t i = 0; i < BATCH; ++i) {
				if (cfg.max_cycles > 0 && cycle_counter >= cfg.max_cycles) {
					g_sim_running.store(false);
					break;
				}
				if ((i & 4095ULL) == 0) {
					uart.poll_pty_input();
				}

				// Rising edge of clk_cpu
				root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 1;
				top->eval_step();

				// Step bit-accurate UART only when active or RX data pending
				uint8_t tx_pin = top->uart_tx_pin;
				if (uart.is_busy() || tx_pin == 0 ||
				    g_rx_queue_size.load(std::memory_order_relaxed) != 0) {
					top->uart_rx_pin = uart.step_cpu_cycle(tx_pin);
				}

				// Falling edge of clk_cpu
				root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = 0;
				top->eval_step();

				// When VSync is disabled, immediately propagate page flips into clk_vga
				if (root->arty_a7_top__DOT__u_soc_top__DOT__vga_no_vsync &&
				    (root->arty_a7_top__DOT__u_soc_top__DOT__vga_display_page !=
				     root->arty_a7_top__DOT__u_soc_top__DOT__u_vga_controller__DOT__active_page)) {
					pulse_vga_cycles(top.get(), 4);
				}

				cycle_counter++;
				fast_frame_cyc++;

				if (!fast_in_vblank && fast_frame_cyc >= (FRAME_CPU_CYCLES - VBLANK_CPU_CYCLES)) {
					fast_in_vblank = true;
					root->arty_a7_top__DOT__u_soc_top__DOT__u_vga_controller__DOT__v_count =
						VGA_V_ACTIVE;
					pulse_vga_cycles(top.get(), 4);
					g_vga_frames.fetch_add(1, std::memory_order_relaxed);
				} else if (fast_in_vblank && fast_frame_cyc >= FRAME_CPU_CYCLES) {
					fast_in_vblank = false;
					fast_frame_cyc = 0;
					root->arty_a7_top__DOT__u_soc_top__DOT__u_vga_controller__DOT__v_count = 0;
					pulse_vga_cycles(top.get(), 2);
				}
			}

			if (g_fast_snapshot_req.exchange(false, std::memory_order_relaxed)) {
				snapshot_fast_vram(top.get());
			}
		} else {
			// Pin-Accurate Mode: dual-clock integer phase scheduler (25 MHz vs 83.46 MHz)
			constexpr uint64_t PIN_EVENTS = 32768;
			for (uint64_t ev = 0; ev < PIN_EVENTS; ++ev) {
				if (cfg.max_cycles > 0 && cycle_counter >= cfg.max_cycles) {
					g_sim_running.store(false);
					break;
				}

				uint64_t next_ps = std::min(next_cpu_edge_ps, next_vga_edge_ps);
				sim_time_ps = next_ps;

				bool cpu_rising = false;
				bool vga_rising = false;

				if (next_cpu_edge_ps == next_ps) {
					clk_cpu_val ^= 1U;
					cpu_rising = (clk_cpu_val == 1U);
					root->arty_a7_top__DOT__u_clk_wiz_cpu__DOT__sim_clk_cpu = clk_cpu_val;
					next_cpu_edge_ps += CPU_HALF_PS;
				}
				if (next_vga_edge_ps == next_ps) {
					clk_vga_val ^= 1U;
					vga_rising = (clk_vga_val == 1U);
					root->arty_a7_top__DOT__u_clk_wiz_vga__DOT__sim_clk_vga = clk_vga_val;
					next_vga_edge_ps += VGA_HALF_PS;
				}

				top->eval_step();

				if (cpu_rising) {
					if ((cycle_counter & 4095ULL) == 0) {
						uart.poll_pty_input();
					}
					uint8_t tx_pin = top->uart_tx_pin;
					if (uart.is_busy() || tx_pin == 0 ||
					    g_rx_queue_size.load(std::memory_order_relaxed) != 0) {
						top->uart_rx_pin = uart.step_cpu_cycle(tx_pin);
					}
					cycle_counter++;
				}
				if (vga_rising) {
					vga_mon.on_vga_posedge(top->vga_hs, top->vga_vs, top->vga_r,
					                       top->vga_g, top->vga_b);
				}
			}
		}

		g_cpu_cycles.store(cycle_counter, std::memory_order_relaxed);

		auto now = std::chrono::steady_clock::now();
		double dt = std::chrono::duration<double>(now - last_time).count();
		if (dt >= 0.5) {
			uint64_t dcyc = cycle_counter - prev_cycles;
			g_last_mhz.store(static_cast<double>(dcyc) / (dt * 1e6),
			                 std::memory_order_relaxed);
			prev_cycles = cycle_counter;
			last_time = now;
		}
	}

	if (!cfg.dump_ppm_path.empty()) {
		if (static_cast<VgaMode>(g_vga_mode.load(std::memory_order_relaxed)) ==
		    VgaMode::Fast) {
			snapshot_fast_vram(top.get());
		}
		uint32_t copy_fb[FB_PIXELS];
		{
			std::lock_guard<std::mutex> lock(g_fb_mutex);
			std::memcpy(copy_fb, g_front_fb, sizeof(copy_fb));
		}
		write_ppm_file(cfg.dump_ppm_path, copy_fb);
		std::cout << "\n[SIM] Wrote VGA frame to " << cfg.dump_ppm_path << "\n";
	}

	top->final();
}

void print_usage(const char *prog) {
	std::cout
		<< "Usage: " << prog << " [options]\n"
		<< "Options:\n"
		<< "  --vga-mode fast|pin   VGA simulation mode (default: fast)\n"
		<< "  --boot <path.mem>     Override initial BRAM contents (.mem hex)\n"
		<< "  --load <path.bin>     Preload raw binary into system RAM\n"
		<< "  --load-addr <hex>     Target byte address for --load (default: 0x10000)\n"
		<< "  --uart-link <path>    Create symlink to the virtual UART PTY device\n"
		<< "  --no-stdout           Do not mirror UART TX bytes to stdout\n"
		<< "  --headless            Run without opening an SDL2 window\n"
		<< "  --max-cycles <N>      Stop after N CPU cycles (default: unlimited)\n"
		<< "  --dump-ppm <path>     Write final 320x200 VGA frame as PPM on exit\n"
		<< "  --help                Show this help\n";
}

bool parse_args(int argc, char **argv, SimConfig &cfg) {
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--help" || arg == "-h") {
			print_usage(argv[0]);
			return false;
		} else if (arg == "--vga-mode" && i + 1 < argc) {
			std::string m = argv[++i];
			if (m == "fast") {
				cfg.vga_mode = VgaMode::Fast;
			} else if (m == "pin") {
				cfg.vga_mode = VgaMode::Pin;
			} else {
				std::cerr << "Unknown --vga-mode: " << m << "\n";
				return false;
			}
		} else if (arg == "--boot" && i + 1 < argc) {
			cfg.boot_mem_path = argv[++i];
		} else if (arg == "--load" && i + 1 < argc) {
			cfg.load_bin_path = argv[++i];
		} else if (arg == "--load-addr" && i + 1 < argc) {
			cfg.load_addr = static_cast<uint32_t>(std::stoul(argv[++i], nullptr, 16));
		} else if (arg == "--uart-link" && i + 1 < argc) {
			cfg.uart_link_path = argv[++i];
		} else if (arg == "--no-stdout") {
			cfg.echo_stdout = false;
		} else if (arg == "--headless") {
			cfg.headless = true;
		} else if (arg == "--max-cycles" && i + 1 < argc) {
			cfg.max_cycles = std::stoull(argv[++i]);
		} else if (arg == "--dump-ppm" && i + 1 < argc) {
			cfg.dump_ppm_path = argv[++i];
		} else if (arg[0] == '+') {
			// Pass through Verilator plusargs
			continue;
		} else {
			std::cerr << "Unknown or incomplete argument: " << arg << "\n";
			print_usage(argv[0]);
			return false;
		}
	}
	return true;
}

} // namespace

int main(int argc, char **argv) {
	SimConfig cfg;
	if (!parse_args(argc, argv, cfg)) {
		return 1;
	}

	g_vga_mode.store(static_cast<int>(cfg.vga_mode), std::memory_order_relaxed);

	UartBridge uart(cfg.echo_stdout, cfg.uart_link_path);
	if (!uart.init()) {
		return 1;
	}

	std::cout << "============================================================\n"
	          << " Risk-V Phase 2 Simulator (Top: arty_a7_top)\n"
	          << " CPU Clock : " << CPU_CLK_FREQ << " Hz | UART Baud : "
	          << UART_BAUD << " (" << CLKS_PER_BIT << " clks/bit)\n"
	          << " VGA Mode  : "
	          << (cfg.vga_mode == VgaMode::Fast ? "FAST (VRAM+VBlank)"
	                                           : "PIN (83.46 MHz pins)")
	          << "\n"
	          << " UART PTY  : " << uart.slave_path() << "\n";
	if (!cfg.uart_link_path.empty()) {
		std::cout << " UART Link : " << cfg.uart_link_path << "\n";
	}
	std::cout << "============================================================\n"
	          << std::flush;

	if (cfg.headless) {
		cpu_simulation_worker(argc, argv, cfg, uart);
		return 0;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
		"Risk-V Arty A7-100T Simulator (arty_a7_top)",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	}
	if (!renderer) {
		std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Texture *texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
		FB_WIDTH, FB_HEIGHT);
	if (!texture) {
		std::cerr << "SDL_CreateTexture failed: " << SDL_GetError() << "\n";
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	std::thread worker(cpu_simulation_worker, argc, argv, std::cref(cfg),
	                   std::ref(uart));

	SDL_StartTextInput();

	const SDL_Rect btn_reset = {15, SCREEN_HEIGHT + 16, 130, 46};
	const SDL_Rect btn_vga = {160, SCREEN_HEIGHT + 16, 175, 46};
	const SDL_Rect btn_paste = {350, SCREEN_HEIGHT + 16, 120, 46};

	uint32_t fps_last_time = SDL_GetTicks();
	int frames_this_sec = 0;
	double last_fps = 0.0;
	uint32_t local_fb[FB_PIXELS] = {0};

	while (g_sim_running.load(std::memory_order_relaxed)) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				g_sim_running.store(false, std::memory_order_relaxed);
			} else if (event.type == SDL_MOUSEBUTTONDOWN &&
			           event.button.button == SDL_BUTTON_LEFT) {
				int mx = event.button.x;
				int my = event.button.y;
				auto hit = [&](const SDL_Rect &r) {
					return mx >= r.x && mx < (r.x + r.w) && my >= r.y &&
					       my < (r.y + r.h);
				};
				if (hit(btn_reset)) {
					g_reset_requested.store(true, std::memory_order_relaxed);
				} else if (hit(btn_vga)) {
					int cur = g_vga_mode.load(std::memory_order_relaxed);
					g_vga_mode.store(cur == 0 ? 1 : 0, std::memory_order_relaxed);
				} else if (hit(btn_paste)) {
					paste_clipboard();
				}
			} else if (event.type == SDL_TEXTINPUT) {
				for (int i = 0; event.text.text[i] != '\0'; ++i) {
					enqueue_uart_rx_byte(static_cast<uint8_t>(event.text.text[i]));
				}
			} else if (event.type == SDL_KEYDOWN) {
				Uint16 mod = event.key.keysym.mod;
				SDL_Keycode sym = event.key.keysym.sym;
				if (sym == SDLK_F1 ||
				    (sym == SDLK_r && (mod & (KMOD_CTRL | KMOD_GUI)))) {
					g_reset_requested.store(true, std::memory_order_relaxed);
				} else if (sym == SDLK_F2) {
					int cur = g_vga_mode.load(std::memory_order_relaxed);
					g_vga_mode.store(cur == 0 ? 1 : 0, std::memory_order_relaxed);
				} else if (sym == SDLK_v && (mod & (KMOD_CTRL | KMOD_GUI))) {
					paste_clipboard();
				} else if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER) {
					enqueue_uart_rx_byte('\r');
				} else if (sym == SDLK_ESCAPE) {
					enqueue_uart_rx_byte(27);
				} else if (sym == SDLK_BACKSPACE) {
					enqueue_uart_rx_byte('\b');
				}
			}
		}

		if (static_cast<VgaMode>(g_vga_mode.load(std::memory_order_relaxed)) ==
		    VgaMode::Fast) {
			g_fast_snapshot_req.store(true, std::memory_order_relaxed);
		}

		if (g_fb_dirty.exchange(false, std::memory_order_acquire)) {
			{
				std::lock_guard<std::mutex> lock(g_fb_mutex);
				std::memcpy(local_fb, g_front_fb, sizeof(local_fb));
			}
			SDL_UpdateTexture(texture, nullptr, local_fb,
			                  FB_WIDTH * static_cast<int>(sizeof(uint32_t)));
		}

		SDL_Rect display_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, &display_rect);

		SDL_Rect panel_rect = {0, SCREEN_HEIGHT, SCREEN_WIDTH, PANEL_HEIGHT};
		SDL_SetRenderDrawColor(renderer, 28, 28, 32, 255);
		SDL_RenderFillRect(renderer, &panel_rect);

		SDL_SetRenderDrawColor(renderer, 64, 64, 72, 255);
		SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH,
		                   SCREEN_HEIGHT);

		// BTN0 RESET button
		SDL_SetRenderDrawColor(renderer, 165, 42, 42, 255);
		SDL_RenderFillRect(renderer, &btn_reset);
		render_text_batched(renderer, "BTN0 RESET", btn_reset.x + 25,
		                    btn_reset.y + 12, {255, 255, 255, 255});
		render_text_batched(renderer, "(F1/Ctrl+R)", btn_reset.x + 21,
		                    btn_reset.y + 27, {220, 220, 220, 255});

		// VGA Mode Toggle button
		bool is_pin =
			static_cast<VgaMode>(g_vga_mode.load(std::memory_order_relaxed)) ==
			VgaMode::Pin;
		if (is_pin) {
			SDL_SetRenderDrawColor(renderer, 175, 105, 20, 255);
		} else {
			SDL_SetRenderDrawColor(renderer, 30, 95, 155, 255);
		}
		SDL_RenderFillRect(renderer, &btn_vga);
		render_text_batched(renderer,
		                    is_pin ? "VGA: PIN (83.5MHz)" : "VGA: FAST (VRAM)",
		                    btn_vga.x + 15, btn_vga.y + 12, {255, 255, 255, 255});
		render_text_batched(renderer, "Press F2 to switch", btn_vga.x + 15,
		                    btn_vga.y + 27, {220, 220, 220, 255});

		// PASTE button
		SDL_SetRenderDrawColor(renderer, 42, 140, 62, 255);
		SDL_RenderFillRect(renderer, &btn_paste);
		render_text_batched(renderer, "PASTE", btn_paste.x + 40,
		                    btn_paste.y + 12, {255, 255, 255, 255});
		render_text_batched(renderer, "(Ctrl+V)", btn_paste.x + 28,
		                    btn_paste.y + 27, {220, 220, 220, 255});

		// Telemetry readouts
		char buf_mhz[40], buf_fps[40], buf_cyc[48], buf_pty[64];
		std::snprintf(buf_mhz, sizeof(buf_mhz), "CPU: %.2f MHz",
		              g_last_mhz.load(std::memory_order_relaxed));
		std::snprintf(buf_fps, sizeof(buf_fps), "UI FPS: %.1f  VGA: %llu",
		              last_fps,
		              static_cast<unsigned long long>(
		                  g_vga_frames.load(std::memory_order_relaxed)));
		std::snprintf(buf_cyc, sizeof(buf_cyc), "Cycles: %llu  RX Q: %zu",
		              static_cast<unsigned long long>(
		                  g_cpu_cycles.load(std::memory_order_relaxed)),
		              g_rx_queue_size.load(std::memory_order_relaxed));
		std::snprintf(buf_pty, sizeof(buf_pty), "PTY: %s",
		              uart.slave_path().c_str());

		render_text_batched(renderer, buf_mhz, 490, SCREEN_HEIGHT + 16,
		                    {230, 230, 230, 255});
		render_text_batched(renderer, buf_fps, 490, SCREEN_HEIGHT + 36,
		                    {200, 225, 255, 255});
		render_text_batched(renderer, buf_cyc, 490, SCREEN_HEIGHT + 56,
		                    {255, 220, 175, 255});
		render_text_batched(renderer, buf_pty, 725, SCREEN_HEIGHT + 16,
		                    {170, 255, 180, 255});

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

	if (worker.joinable()) {
		worker.join();
	}

	SDL_StopTextInput();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

double sc_time_stamp() { return 0; }
