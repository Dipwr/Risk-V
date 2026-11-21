OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
	/* 192 KB User RAM starting at 0x00010000 (leaving lower 64 KB for Wozmon) */
	RAM (rwx) : ORIGIN = 0x00010000, LENGTH = 192K
}

/* Stack top at ceiling of 256 KB Main RAM; 32 KB stack reserve below _stack_top */
_stack_top  = 0x0003FFF0;
_heap_limit = 0x00038000;

SECTIONS
{
	.text : {
		. = ALIGN(4);
		*(.text.boot)
		*(.text*)
		*(.rodata*)
		*(.srodata*)
		. = ALIGN(4);
	} > RAM

	.data : {
		. = ALIGN(4);
		*(.data*)
		*(.sdata*)
		. = ALIGN(4);
	} > RAM

	/* Global pointer for RISC-V small data relaxation */
	. = ALIGN(8);
	__global_pointer$ = . + 0x800;

	.bss : {
		. = ALIGN(4);
		__bss_start = .;
		*(.sbss*)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end = .;
	} > RAM

	. = ALIGN(8);
	_end = .;
	PROVIDE(end = .);
}
