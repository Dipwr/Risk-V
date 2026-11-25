OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
	/* Lower 8 KB of BRAM reserved for UART binary bootloader */
	RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 8K
}

_stack_top = 0x00001FF0;

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
}
