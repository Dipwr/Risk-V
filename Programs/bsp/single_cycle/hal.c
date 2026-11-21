#include "bsp.h"

#define PAGE_REG ((volatile uint32_t *)0x00080000)
#define TERM_OUT ((volatile uint32_t *)0x00080004)
#define KEY_DATA ((volatile uint32_t *)0x00080020)
#define KEY_STAT ((volatile uint32_t *)0x00080024)

static int g_cur_page = 0;

void bsp_set_page(int page) {
  g_cur_page = page & 1;
  *PAGE_REG = (uint32_t)g_cur_page;
}

void bsp_set_vsync(int enable) { (void)enable; }

int bsp_vblank(void) { return 0; }

int bsp_active_page(void) { return g_cur_page; }

void bsp_wait_vblank(void) {}

void bsp_present_page(int page) { bsp_set_page(page); }

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
