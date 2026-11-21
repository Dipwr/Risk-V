OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
	/* 256 KB Unified User RAM starting at 0x00040000 (Phase 1 Single-Cycle) */
	RAM (rwx) : ORIGIN = 0x00040000, LENGTH = 256K
}

/* Stack top at ceiling of RAM; 32 KB stack reserve below _stack_top */
_stack_top  = 0x0007FFF0;
_heap_limit = 0x00078000;

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
