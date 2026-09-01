#include "FreeRTOS.h"
#include "task.h"

extern void xPortStartFirstTask(void);

/* Initialize Task Stack Frame (32 Integer Registers: x1 - x31, PC) */
StackType_t *pxPortInitialiseStack(StackType_t *pxTopOfStack,
                                   TaskFunction_t pxCode, void *pvParameters) {
  // 16-byte stack alignment
  pxTopOfStack = (StackType_t *)((uintptr_t)pxTopOfStack & ~0xF);

  pxTopOfStack -= 32; // Reserve space for 32 registers

  pxTopOfStack[0] = (StackType_t)pxCode;       // ra: Task entry point
  pxTopOfStack[7] = (StackType_t)pvParameters; // a0: Parameter passed to task

  return pxTopOfStack;
}

BaseType_t xPortStartScheduler(void) {
  xPortStartFirstTask();
  return pdFALSE;
}

void vPortEndScheduler(void) {}