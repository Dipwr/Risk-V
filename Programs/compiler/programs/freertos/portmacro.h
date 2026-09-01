#ifndef PORTMACRO_H
#define PORTMACRO_H

#include <stddef.h>
#include <stdint.h>

/* Type definitions */
#define portCHAR char
#define portFLOAT float
#define portDOUBLE double
#define portLONG int32_t
#define portSHORT int16_t
#define portSTACK_TYPE uint32_t
#define portBASE_TYPE int32_t

typedef portSTACK_TYPE StackType_t;
typedef int32_t BaseType_t;
typedef uint32_t UBaseType_t;
typedef uint32_t TickType_t;

#define portMAX_DELAY ((TickType_t)0xffffffffUL)
#define portSTACK_GROWTH (-1)
#define portTICK_PERIOD_MS ((TickType_t)1000 / configTICK_RATE_HZ)
#define portBYTE_ALIGNMENT 16

/* Task function definition macros (Required by FreeRTOS tasks.c) */
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters)                       \
  void vFunction(void *pvParameters)
#define portTASK_FUNCTION(vFunction, pvParameters)                             \
  void vFunction(void *pvParameters)

#define portNOP() __asm__ volatile("nop")
#define portINLINE __inline

/* Context switch prototypes */
void vPortYield(void);
#define portYIELD() vPortYield()

/* Critical section management */
#define portDISABLE_INTERRUPTS()
#define portENABLE_INTERRUPTS()
#define portENTER_CRITICAL()
#define portEXIT_CRITICAL()

#endif /* PORTMACRO_H */