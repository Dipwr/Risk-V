.section .text.boot
.global _start
.type _start, @function

_start:
	# 1. Initialize Global Pointer (Disable linker relaxation for this instruction)
	.option push
	.option norelax
	la   gp, __global_pointer$
	.option pop

	# 2. Initialize Stack Pointer at top of 256 KB RAM (0x0003FFF0)
	la   sp, _stack_top

	# 3. Zero-out BSS section (uninitialized globals)
	la   t0, __bss_start
	la   t1, __bss_end
1:
	bgeu t0, t1, 2f
	sw   zero, 0(t0)
	addi t0, t0, 4
	j    1b
2:
	# 4. Call C main entry point
	call main

	# 5. If main returns: reset display to Page 0 and jump directly to Wozmon ROM
	li   t0, 0x20000008     # PAGE_REG MMIO address in our SoC
	sw   zero, 0(t0)        # Switch display back to Page 0
	li   t1, 0x00000000     # Wozmon Boot ROM Entry Address
	jr   t1                 # Jump to Wozmon!