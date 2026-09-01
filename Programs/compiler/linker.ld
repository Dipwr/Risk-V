OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    /* 256 KB Unified RAM starting at 0x00040000 */
    RAM (rwx) : ORIGIN = 0x00040000, LENGTH = 256K
}

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