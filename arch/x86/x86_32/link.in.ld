#include <arch/vaddr.h>

ENTRY(_start)
SECTIONS
{
    . = CONFIG_X86_BASE_ADDR + CONFIG_X86_LOAD_ADDR;

    .text ALIGN(4K) : AT(virt_to_phys(ADDR(.text))) {
        *(.multiboot)
        *(.text .text.*)
    }

    .rodata ALIGN(4K) : AT(virt_to_phys(ADDR(.rodata))) {
        *(.rodata .rodata.*)
    }

    .data ALIGN(4K) : AT(virt_to_phys(ADDR(.data))) {
        *(.data .data.*)
    }

    .bss ALIGN(4K) : AT(virt_to_phys(ADDR(.bss))) {
        *(COMMON)
        *(.bss .bss.*)
    }
}
