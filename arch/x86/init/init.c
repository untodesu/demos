#include <arch/drivers/serial.h>
#include <arch/interrupts.h>
#include <arch/segment.h>
#include <demos/cdefs.h>
#include <demos/kprintf.h>

static void kprintf_serial(const void *s, size_t n)
{
    serial_write(SERIAL0, s, n);
}

static void handler_42(struct interrupt_frame *frame)
{
    kprintf("int $0x42 is called!\r\n");
#if defined(X86_64)
    kprintf("RIP = 0x%016llX\r\n", frame->rip);
#else
    kprintf("EIP = 0x%08X\r\n", frame->eip);
#endif
}

static void __noreturn hang(void)
{
    for(;;) asm volatile("hlt");
}

void __noreturn init_arch(void)
{
    disable_interrupts();

    if(init_serial(SERIAL0, 8000))
        set_kprintf_func(kprintf_serial);

    init_segment();
    init_interrupts();

    set_interrupt_handler(0x42, handler_42);
    enable_interrupts();
    asm volatile("int $0x42");

    kprintf("Off to hang myself! Watch and lea--\r\n");
    hang();
}
