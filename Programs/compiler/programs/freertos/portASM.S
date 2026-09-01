.section .text
.align 4
.global vPortYield
.global xPortStartFirstTask
.type vPortYield, @function
.type xPortStartFirstTask, @function

# ============================================================================
# CONTEXT SWITCH ROUTINE: vPortYield()
# ============================================================================
vPortYield:
    # 1. Save all 32 general-purpose registers onto current task stack
    addi sp, sp, -128
    sw   ra,   0(sp)
    sw   tp,   4(sp)
    sw   t0,   8(sp)
    sw   t1,  12(sp)
    sw   t2,  16(sp)
    sw   s0,  20(sp)
    sw   s1,  24(sp)
    sw   a0,  28(sp)
    sw   a1,  32(sp)
    sw   a2,  36(sp)
    sw   a3,  40(sp)
    sw   a4,  44(sp)
    sw   a5,  48(sp)
    sw   a6,  52(sp)
    sw   a7,  56(sp)
    sw   s2,  60(sp)
    sw   s3,  64(sp)
    sw   s4,  68(sp)
    sw   s5,  72(sp)
    sw   s6,  76(sp)
    sw   s7,  80(sp)
    sw   s8,  84(sp)
    sw   s9,  88(sp)
    sw   s10, 92(sp)
    sw   s11, 96(sp)
    sw   t3, 100(sp)
    sw   t4, 104(sp)
    sw   t5, 108(sp)
    sw   t6, 112(sp)

    # 2. Save current SP into pxCurrentTCB
    la   t0, pxCurrentTCB
    lw   t1, 0(t0)
    sw   sp, 0(t1)

    # 3. Call FreeRTOS kernel to pick next task to run
    call vTaskSwitchContext

# ============================================================================
# RESTORE & START TASK ROUTINE
# ============================================================================
xPortStartFirstTask:
    # 4. Load SP from new task's TCB
    la   t0, pxCurrentTCB
    lw   t1, 0(t0)
    lw   sp, 0(t1)

    # 5. Restore registers from new task stack
    lw   ra,   0(sp)
    lw   tp,   4(sp)
    lw   t0,   8(sp)
    lw   t1,  12(sp)
    lw   t2,  16(sp)
    lw   s0,  20(sp)
    lw   s1,  24(sp)
    lw   a0,  28(sp)
    lw   a1,  32(sp)
    lw   a2,  36(sp)
    lw   a3,  40(sp)
    lw   a4,  44(sp)
    lw   a5,  48(sp)
    lw   a6,  52(sp)
    lw   a7,  56(sp)
    lw   s2,  60(sp)
    lw   s3,  64(sp)
    lw   s4,  68(sp)
    lw   s5,  72(sp)
    lw   s6,  76(sp)
    lw   s7,  80(sp)
    lw   s8,  84(sp)
    lw   s9,  88(sp)
    lw   s10, 92(sp)
    lw   s11, 96(sp)
    lw   t3, 100(sp)
    lw   t4, 104(sp)
    lw   t5, 108(sp)
    lw   t6, 112(sp)
    addi sp, sp, 128

    # 6. Jump to task
    ret