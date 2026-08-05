.section .text.boot
.globl _start

_start:
	# Load stack pointer to top of RAM
	la	sp, __stack_top

	# Execute C main function
	jal	ra, main

	# Force return address back to Wozmon (0x00000000)
	li	ra, 0x00000000
	ret