#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>

// --- Compiler Interface Configurations ---
#define CC_CONF_REGISTER_ARGS 1
#define CC_CONF_FUNCTION_POINTER_ARGS 1
#define CC_CONF_VA_ARGS 1
#define CC_CONF_INLINE inline
#define CCIF // Empty macro for GCC function export
#define CLIF // Empty macro for GCC library export

// --- Clock Configuration ---
#define CLOCK_CONF_SECOND 1000
typedef uint32_t clock_time_t;

// --- Legacy Contiki Type Aliases ---
typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef int8_t s8_t;
typedef int16_t s16_t;
typedef int32_t s32_t;

// --- Character & Keyboard Navigation Keys (Positive values for unsigned char)
#define ctk_arch_isprint(c) ((c) >= 32 && (c) <= 126)

#define CH_ENTER '\r'
#define CH_DEL '\b'
#define CH_CURS_UP 0x81
#define CH_CURS_LEFT 0x82
#define CH_CURS_RIGHT 0x83
#define CH_CURS_DOWN 0x84

#define CTK_CONF_MENU_KEY 0x85         // F10 / Menu key
#define CTK_CONF_WINDOWSWITCH_KEY 0x86 // Window cycle key
#define CTK_CONF_WIDGETUP_KEY 0x87     // Shift-Tab
#define CTK_CONF_WIDGETDOWN_KEY '\t'   // Tab key

// --- CTK Desktop Window Manager Configuration ---
#define CTK_CONF_SCREEN_WIDTH 40  // 320 px / 8 px font
#define CTK_CONF_SCREEN_HEIGHT 25 // 200 px / 8 px font
#define CTK_CONF_WINDOWS 1        // Multi-window desktop engine
#define CTK_CONF_WINDOWMOVE 1     // Draggable windows
#define CTK_CONF_WINDOWCLOSE 1    // Window close buttons
#define CTK_CONF_MENUS 1          // Top drop-down menu bar
#define CTK_CONF_MENUWIDTH 16     // Menu column width
#define CTK_CONF_MAXMENUITEMS 10  // Max items per menu
#define CTK_CONF_MOUSE_SUPPORT 1  // Enable mouse tracking
#define CTK_CONF_ICONS 1          // Desktop icons
#define CTK_CONF_ICON_BITMAPS 0
#define CTK_CONF_ICON_TEXTMAPS 1
#define CTK_CONF_WIDGET_FLAGS 0
#define CTK_CONF_SCREENSAVER 0

// --- In-Memory File System (CFS) ---
#define CFS_RAM_CONF_SIZE (32 * 1024)
#define AUTOSTART_ENABLE 0
#define DSC_CONF_LOADER 1

// --- Dynamic Program Loader & DSC ---
#define WITH_LOADER_ARCH 1

#endif