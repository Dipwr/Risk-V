/* ============================================================================
 * NEWLIB SYSTEM CALL STUBS FOR RV32IM BARE-METAL CORE
 * ============================================================================
 */

#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>

#define UART_DATA ((volatile uint32_t *)0x20000000)
#define UART_STAT ((volatile uint32_t *)0x20000004)
#define PAGE_REG  ((volatile uint32_t *)0x20000008)

#define UART_RX_READY (1U << 0)
#define UART_TX_READY (1U << 1)

// Weak hook to screen renderer (if implemented by application)
extern void term_putc(char c) __attribute__((weak));

// 1. Terminal Output: connects printf(), puts(), putchar() to both UART and
// Screen
int _write(int file, char *ptr, int len) {
  (void)file;
  for (int i = 0; i < len; i++) {
    char c = *ptr++;
    while (!(*UART_STAT & UART_TX_READY))
      ;
    *UART_DATA = (uint32_t)(uint8_t)c; // Send to UART TX FIFO

    if (term_putc) {
      term_putc(c); // Draw to 320x200 Framebuffer!
    }
  }
  return len;
}

// 2. Keyboard / UART Input
int _read(int file, char *ptr, int len) {
  (void)file;
  int count = 0;
  while (count < len) {
    if (*UART_STAT & UART_RX_READY) {
      *ptr++ = (char)(*UART_DATA);
      count++;
    }
  }
  return count;
}

// 3. Dynamic Heap Management (256 KB RAM: _stack_top at 0x0003FFF0, 32 KB stack reserve)
extern char _end;
static char *heap_ptr = &_end;
#define STACK_LIMIT ((char *)0x00038000)

void *_sbrk(ptrdiff_t incr) {
  char *prev_heap = heap_ptr;
  if ((heap_ptr + incr >= STACK_LIMIT) || (heap_ptr + incr < &_end)) {
    return (void *)-1;
  }
  heap_ptr += incr;
  return prev_heap;
}

int _close(int file) {
  (void)file;
  return -1;
}
int _fstat(int file, struct stat *st) {
  (void)file;
  st->st_mode = S_IFCHR;
  return 0;
}
int _isatty(int file) {
  (void)file;
  return 1;
}
int _lseek(int file, int ptr, int dir) {
  (void)file;
  (void)ptr;
  (void)dir;
  return 0;
}
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  return -1;
}
int _getpid(void) { return 1; }

void _exit(int status) {
  (void)status;
  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
  while (1)
    ;
}