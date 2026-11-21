#include "bsp.h"

#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

void bsp_set_page(int page) { *PAGE_REG = (uint32_t)(page & 1); }

int bsp_vblank(void) { return 0; }

void bsp_putc(char c) { *TERM_OUT = (uint32_t)(uint8_t)c; }

void bsp_puts(const char *s) {
  while (*s) {
    bsp_putc(*s++);
  }
}

int bsp_key_avail(void) { return (int)(*KEY_STAT & 0x1U); }

char bsp_getc(void) {
  while (!bsp_key_avail())
    ;
  return (char)(*KEY_DATA & 0xFFU);
}

char bsp_try_getc(void) {
  if (!bsp_key_avail())
    return 0;
  return (char)(*KEY_DATA & 0xFFU);
}

void bsp_exit(void) {
  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
  while (1)
    ;
}
