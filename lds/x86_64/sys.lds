#define FLAG_E (1 << 0)
#define FLAG_W (1 << 1)
#define FLAG_R (1 << 2)

PHDRS
{
    null    PT_NULL FLAGS(  0               );
    text    PT_LOAD FLAGS(  FLAG_E | FLAG_R );
    rodata  PT_LOAD FLAGS(  FLAG_R          );
    data    PT_LOAD FLAGS(  FLAG_W | FLAG_R );
}

SECTIONS
{
    . = 0xFFFFFFFF80000000;

    .text ALIGN(CONSTANT(MAXPAGESIZE)) : {
        *(.text)
        *(.text.*)
    } :text

    .rodata ALIGN(CONSTANT(MAXPAGESIZE)) : {
        *(.rodata)
        *(.rodata.*)
    } :rodata

    .data ALIGN(CONSTANT(MAXPAGESIZE)) : {
        *(.data)
        *(.data.*)
    } :data

    .bss ALIGN(CONSTANT(MAXPAGESIZE)) : {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    } :data
}
