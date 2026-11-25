.section .text.boot
.global _start
.type _start, @function

_start:
	.option push
	.option norelax
	la   gp, __global_pointer$
	.option pop

	la   sp, _stack_top

	la   t0, __bss_start
	la   t1, __bss_end
1:
	bgeu t0, t1, 2f
	sw   zero, 0(t0)
	addi t0, t0, 4
	j    1b
2:
	call boot_main
3:
	j    3b
