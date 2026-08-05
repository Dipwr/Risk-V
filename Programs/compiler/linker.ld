MEMORY
{
	RAM (rwx) : ORIGIN = 0x00040000, LENGTH = 256K
}

SECTIONS
{
	/* All code and constants go straight into RAM */
	.text :
	{
		*(.text.boot)   /* Boot wrapper comes first */
		*(.text*)
		*(.rodata*)
	} > RAM

	/* Global variables live right after code in RAM */
	.data :
	{
		*(.data*)
	} > RAM

	.bss :
	{
		__bss_start = .;
		*(.bss*)
		*(COMMON)
		__bss_end = .;
	} > RAM

	/* Set stack pointer to the top of RAM */
	__stack_top = ORIGIN(RAM) + LENGTH(RAM);
}