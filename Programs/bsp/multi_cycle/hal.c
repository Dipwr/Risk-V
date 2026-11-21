#include "bsp.h"

#define UART_DATA ((volatile uint32_t *)0x20000000)
#define UART_STAT ((volatile uint32_t *)0x20000004)
#define PAGE_REG  ((volatile uint32_t *)0x20000008)

#define UART_RX_READY (1U << 0)
#define UART_TX_READY (1U << 1)
#define VGA_VBLANK    (1U << 1)

void bsp_set_page(int page) { *PAGE_REG = (uint32_t)(page & 1); }

int bsp_vblank(void) { return (int)((*PAGE_REG & VGA_VBLANK) != 0); }

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
  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
  while (1)
    ;
}
