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
#define BSP_TARGET_NAME   "multi_cycle"
#define BSP_VRAM_BASE     ((volatile uint16_t *)0x10000000)
#define BSP_PAGE_STRIDE   65536U
#define BSP_CLINT_BASE    0x02000000UL
#define BSP_MTIME_BASE    0x02000000UL
#define BSP_MTIMECMP_BASE 0x02000008UL
#define BSP_MTIME_LO      ((volatile uint32_t *)0x02000000UL)
#define BSP_MTIME_HI      ((volatile uint32_t *)0x02000004UL)
#define BSP_MTIMECMP_LO   ((volatile uint32_t *)0x02000008UL)
#define BSP_MTIMECMP_HI   ((volatile uint32_t *)0x0200000CUL)
#define BSP_TIMER_FREQ_HZ 1000000UL
#define BSP_IRQ_EN        ((volatile uint32_t *)0x02000010UL)
#define BSP_IRQ_PEND      ((volatile uint32_t *)0x02000014UL)
#define BSP_SYS_RESET     ((volatile uint32_t *)0x0200001CUL)
#define BSP_IRQ_UART_RX   (1U << 0)
#define BSP_IRQ_VBLANK    (1U << 1)
#define BSP_SYS_RESET_KEY 0x52535401UL
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
uint64_t bsp_time_us(void);
uint32_t bsp_time_ms(void);
void bsp_delay_us(uint32_t us);
void bsp_delay_ms(uint32_t ms);
void bsp_timer_set_cmp(uint64_t cmp);
void bsp_timer_set_relative_us(uint64_t delta_us);
void bsp_timer_disable(void);
void bsp_irq_enable(uint32_t mask);
void bsp_irq_disable(uint32_t mask);
uint32_t bsp_irq_pending(void);
void bsp_irq_clear(uint32_t mask);
void bsp_soft_reset(void) __attribute__((noreturn));
void bsp_exit(void) __attribute__((noreturn));

#endif /* BSP_H */
