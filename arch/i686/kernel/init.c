#include <arch/i8253.h>
#include <arch/interrupts.h>
#include <arch/segment.h>
#include <arch/serial.h>
#include <demos/cdefs.h>
#include <demos/kprintf.h>

static void kprintf_serial(const void *s, size_t n)
{
    serial_write(SERIAL0, s, n);
}

static void __noreturn hang(void)
{
    for(;;) asm volatile("hlt");
}

void __noreturn arch_init(void)
{
    disable_interrupts();

    init_segment();
    init_interrupts();

    /* On this stage we would print something
     * but text-mode UI seems a bit too hard
     * to manage, so we use a serial port for
     * kprintf() to print to. */
    if(init_serial(SERIAL0, 8000))
        set_kprintf_func(kprintf_serial);

    init_i8253();

    kprintf("Off to hang myself, watch and lea--\r\n");
    hang();
}
