#include "bsp.h"

#define UART_DATA ((volatile uint32_t *)0x20000000)
#define UART_STAT ((volatile uint32_t *)0x20000004)
#define PAGE_REG  ((volatile uint32_t *)0x20000008)

#define UART_RX_READY   (1U << 0)
#define UART_TX_READY   (1U << 1)
#define VGA_NO_VSYNC_W  (1U << 1)
#define VGA_VBLANK      (1U << 1)
#define VGA_ACTIVE_PAGE (1U << 2)
#define VGA_NO_VSYNC_R  (1U << 3)

static uint32_t g_no_vsync = 0;

void bsp_set_page(int page) { *PAGE_REG = (uint32_t)(page & 1) | g_no_vsync; }

void bsp_set_vsync(int enable) {
  g_no_vsync = enable ? 0U : VGA_NO_VSYNC_W;
  *PAGE_REG = (*PAGE_REG & 1U) | g_no_vsync;
}

int bsp_vblank(void) { return (int)((*PAGE_REG & VGA_VBLANK) != 0); }

int bsp_active_page(void) { return (int)((*PAGE_REG & VGA_ACTIVE_PAGE) != 0); }

void bsp_wait_vblank(void) {
  while (bsp_vblank())
    ;
  while (!bsp_vblank())
    ;
}

void bsp_present_page(int page) {
  int target = page & 1;
  bsp_set_page(target);
  while (bsp_active_page() != target)
    ;
}

void bsp_putc(char c) {
  if (c == '\n') {
    while (!(*UART_STAT & UART_TX_READY))
      ;
    *UART_DATA = (uint32_t)'\r';
  }
  while (!(*UART_STAT & UART_TX_READY))
    ;
  *UART_DATA = (uint32_t)(uint8_t)c;
}

void bsp_puts(const char *s) {
  while (*s) {
    bsp_putc(*s++);
  }
}

int bsp_key_avail(void) { return (int)((*UART_STAT & UART_RX_READY) != 0); }

char bsp_getc(void) {
  while (!bsp_key_avail())
    ;
  return (char)(*UART_DATA & 0xFFU);
}

char bsp_try_getc(void) {
  if (!bsp_key_avail())
    return 0;
  return (char)(*UART_DATA & 0xFFU);
}

void bsp_exit(void) {
  g_no_vsync = 0;
  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
  while (1)
    ;
}
