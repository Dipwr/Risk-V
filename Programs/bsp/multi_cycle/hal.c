#include "bsp.h"

#define UART_DATA ((volatile uint32_t *)0x20000000)
#define UART_STAT ((volatile uint32_t *)0x20000004)
#define PAGE_REG  ((volatile uint32_t *)0x20000008)

#define UART_RX_READY   (1U << 0)
#define UART_TX_READY   (1U << 1)
#define UART_TX_IDLE    (1U << 4)
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

uint64_t bsp_time_us(void) {
  uint32_t hi0, lo, hi1;
  do {
    hi0 = *BSP_MTIME_HI;
    lo  = *BSP_MTIME_LO;
    hi1 = *BSP_MTIME_HI;
  } while (hi0 != hi1);
  return ((uint64_t)hi0 << 32) | (uint64_t)lo;
}

uint32_t bsp_time_ms(void) {
  return (uint32_t)(bsp_time_us() / 1000ULL);
}

void bsp_delay_us(uint32_t us) {
  uint64_t start = bsp_time_us();
  while ((bsp_time_us() - start) < (uint64_t)us)
    ;
}

void bsp_delay_ms(uint32_t ms) {
  uint64_t start = bsp_time_us();
  uint64_t wait  = (uint64_t)ms * 1000ULL;
  while ((bsp_time_us() - start) < wait)
    ;
}

void bsp_timer_set_cmp(uint64_t cmp) {
  *BSP_MTIMECMP_LO = 0xFFFFFFFFU;
  *BSP_MTIMECMP_HI = (uint32_t)(cmp >> 32);
  *BSP_MTIMECMP_LO = (uint32_t)(cmp & 0xFFFFFFFFU);
}

void bsp_timer_set_relative_us(uint64_t delta_us) {
  bsp_timer_set_cmp(bsp_time_us() + delta_us);
}

void bsp_timer_disable(void) {
  *BSP_MTIMECMP_LO = 0xFFFFFFFFU;
  *BSP_MTIMECMP_HI = 0xFFFFFFFFU;
}

void bsp_irq_enable(uint32_t mask) { *BSP_IRQ_EN |= mask; }

void bsp_irq_disable(uint32_t mask) { *BSP_IRQ_EN &= ~mask; }

uint32_t bsp_irq_pending(void) { return *BSP_IRQ_PEND; }

void bsp_irq_clear(uint32_t mask) { *BSP_IRQ_PEND = mask; }

void bsp_soft_reset(void) {
  while (!(*UART_STAT & UART_TX_IDLE))
    ;
  *BSP_SYS_RESET = BSP_SYS_RESET_KEY;
  while (1)
    ;
}

void bsp_exit(void) {
  __asm__ volatile("csrci mstatus, 8\n\tcsrw mie, zero" ::: "memory");
  bsp_timer_disable();
  *BSP_IRQ_EN = 0U;
  g_no_vsync = 0;
  *PAGE_REG = 0;
  bsp_soft_reset();
}
