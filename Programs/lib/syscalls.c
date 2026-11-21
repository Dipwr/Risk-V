/* ============================================================================
 * NEWLIB SYSTEM CALL STUBS FOR RV32IM BARE-METAL CORE
 * ============================================================================
 */

#include "bsp.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>

// Weak hook to screen renderer (if implemented by application)
extern void term_putc(char c) __attribute__((weak));

// 1. Terminal Output: connects printf(), puts(), putchar() to BSP console +
// optional screen renderer
int _write(int file, char *ptr, int len) {
  (void)file;
  for (int i = 0; i < len; i++) {
    char c = *ptr++;
    bsp_putc(c);

    if (term_putc) {
      term_putc(c);
    }
  }
  return len;
}

// 2. Keyboard / UART Input
int _read(int file, char *ptr, int len) {
  (void)file;
  int count = 0;
  while (count < len) {
    *ptr++ = bsp_getc();
    count++;
  }
  return count;
}

// 3. Dynamic Heap Management (bounds defined in target linker.ld)
extern char _end;
extern char _heap_limit;
static char *heap_ptr = &_end;

void *_sbrk(ptrdiff_t incr) {
  char *prev_heap = heap_ptr;
  if ((heap_ptr + incr >= &_heap_limit) || (heap_ptr + incr < &_end)) {
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
  bsp_exit();
}
