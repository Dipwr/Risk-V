#ifndef BSP_H
#define BSP_H

#include <stdint.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS   (SCREEN_WIDTH * SCREEN_HEIGHT)

#if defined(TARGET_SINGLE_CYCLE)
#define BSP_TARGET_NAME "single_cycle"
#define BSP_VRAM_BASE   ((volatile uint16_t *)0x00082000)
#define BSP_PAGE_STRIDE 64000U
#elif defined(TARGET_MULTI_CYCLE)
#define BSP_TARGET_NAME "multi_cycle"
#define BSP_VRAM_BASE   ((volatile uint16_t *)0x10000000)
#define BSP_PAGE_STRIDE 65536U
#else
#error "Define either TARGET_SINGLE_CYCLE or TARGET_MULTI_CYCLE"
#endif

static inline volatile uint16_t *bsp_vram_page(int page) {
  return &BSP_VRAM_BASE[(uint32_t)page * BSP_PAGE_STRIDE];
}

void bsp_set_page(int page);
void bsp_set_vsync(int enable);
int bsp_vblank(void);
int bsp_active_page(void);
void bsp_wait_vblank(void);
void bsp_present_page(int page);
void bsp_putc(char c);
void bsp_puts(const char *s);
int bsp_key_avail(void);
char bsp_getc(void);
char bsp_try_getc(void);
void bsp_exit(void) __attribute__((noreturn));

#endif /* BSP_H */
