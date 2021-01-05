#include <arch/interrupts.h>
#include <arch/serial.h>
#include <demos/compiler.h>

static void handler(struct interrupt_frame *frame)
{
    (void)(frame);
    
    // still funny
    const char str[] = "LUNCH TIME MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n";
    serial_write(0, str, sizeof(str) - 1);
}

void __noreturn early_init(void)
{
    init_serial(0, SERIAL_DEFAULT_RATE);
    init_interrupts();

    set_interrupt_handler(0x80, handler);
    asm volatile("int $0x80");

    for(;;);
}
