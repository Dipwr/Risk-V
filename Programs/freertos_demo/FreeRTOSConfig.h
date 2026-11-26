#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Preemptive multitasking via CLINT mtime/mtimecmp Machine Timer Interrupt */
#define configUSE_PREEMPTION                    1
#define configUSE_TIME_SLICING                  1
#define configMTIME_BASE_ADDRESS                0x02000000UL
#define configMTIMECMP_BASE_ADDRESS             0x02000008UL
#define configISR_STACK_SIZE_WORDS              256

/* FreeRTOS RISC-V port.c uses configCPU_CLOCK_HZ as the mtime tick frequency (1 MHz prescaler) */
#define configCPU_CLOCK_HZ                      (1000000UL)
#define configTICK_RATE_HZ                      ((TickType_t)1000)
#define configMAX_PRIORITIES                    4
#define configMINIMAL_STACK_SIZE                ((unsigned short)256)
#define configTOTAL_HEAP_SIZE                   ((size_t)(32 * 1024))
#define configMAX_TASK_NAME_LEN                 16
#define configTICK_TYPE_WIDTH_IN_BITS           TICK_TYPE_WIDTH_32_BITS
#define configIDLE_SHOULD_YIELD                 1

#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_TIMERS                        0
#define configUSE_MUTEXES                       1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               0

#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configSUPPORT_STATIC_ALLOCATION         0

#define INCLUDE_vTaskPrioritySet                0
#define INCLUDE_uxTaskPriorityGet               0
#define INCLUDE_vTaskDelete                     0
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 0
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1

#define configASSERT(x) do { if ((x) == 0) { taskDISABLE_INTERRUPTS(); for (;;) {} } } while (0)

#endif /* FREERTOS_CONFIG_H */
