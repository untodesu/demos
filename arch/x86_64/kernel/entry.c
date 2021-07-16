#include <arch/interrupts.h>
#include <arch/segment.h>
#include <arch/serial.h>
#include <arch/stivale2.h>
#include <config.h>
#include <demos/cdefs.h>
#include <demos/kprintf.h>

static void kprintf_func_serial(const void *s, size_t n)
{
    serial_write(SERIAL0, s, n);
}

static void test_handle(struct interrupt_frame *frame)
{
    kprintf("Int $0x42 has been called!\n");
    kprintf("RIP: %016llX\n", frame->rip);
}

static void __noreturn kmain(struct stivale2_struct *stivale)
{
    init_segment();
    init_interrupts();
    if(!init_serial(SERIAL0, 8000))
        goto hang;
    set_kprintf_func(kprintf_func_serial);
    set_interrupt_handler(0x42, test_handle);
    asm volatile("int $0x42");
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
