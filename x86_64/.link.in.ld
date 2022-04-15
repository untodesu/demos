#include <sys/mmdefs.h>

SECTIONS
{
    . = (VMEM_CODE_BASE + PMEM_LOAD_BASE);

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
