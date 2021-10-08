#define LOAD_ADDR 0xFFFFFFFF80200000

SECTIONS
{
    . = LOAD_ADDR;

    .stivale2hdr ALIGN(4K) : {
        *(.stivale2hdr)
        *(.stivale2hdr.*)
    }

    .text ALIGN(4K) : {
        *(.text)
        *(.text.*)
    }

    .data ALIGN(4K) : {
        *(.data)
        *(.data.*)
    }

    .rodata ALIGN(4K) : {
        *(.rodata)
        *(.rodata.*)
    }

    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }
}
