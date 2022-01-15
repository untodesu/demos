#include <x86/vaddr.h>

ENTRY(_start)
SECTIONS
{
    . = (KERNEL_VIRTUAL_BASE + KERNEL_LOAD_ADDRESS);

    .text ALIGN(4096) : {
        *(.text)
        *(.text.*)
    }

    .stivale2hdr ALIGN(4096) : {
        KEEP(*(.stivale2hdr))
    }

    .rodata ALIGN(4096) : {
        *(.rodata)
        *(.rodata.*)
    }

    .data ALIGN(4096) : {
        *(.data)
        *(.data.*)
    }

    .bss ALIGN(4096) : {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }
}
