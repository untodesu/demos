#include <arch/address.h>

ENTRY(_start)
SECTIONS
{
    . = CONFIG_BASE_ADDR + CONFIG_LOAD_ADDR;

    .text ALIGN(4K) : AT(V2P(ADDR(.text)))
    {
        *(.multiboot)
        *(.text .text.*)
    }

    .rodata ALIGN(4K) : AT(V2P(ADDR(.rodata)))
    {
        *(.rodata .rodata.*)
    }

    .data ALIGN(4K) : AT(V2P(ADDR(.data)))
    {
        *(.data .data.*)
    }

    .bss ALIGN(4K) : AT(V2P(ADDR(.bss)))
    {
        *(COMMON)
        *(.bss .bss.*)
    }
}
