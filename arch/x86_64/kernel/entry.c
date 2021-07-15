#include <arch/serial.h>
#include <arch/stivale2.h>
#include <config.h>
#include <demos/cdefs.h>

static void __noreturn kmain(struct stivale2_struct *stivale)
{
    if(!init_serial(SERIAL0, 8000))
        goto hang;
    serial_write(SERIAL0, "Test message", 12);
hang:
    for(;;) asm volatile("hlt");
}

__section(".bss") static uint8_t stack[CONFIG_X86_STACK_SIZE];
__section(".stivale2hdr") __used static struct stivale2_header header = {
    .entry_point = (uint64_t)(&kmain),
    .stack = (uint64_t)(stack + sizeof(stack)),
    .flags = (1 << 0),
    .tags = 0
};
