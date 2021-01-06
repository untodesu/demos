#include <arch/i8259.h>
#include <arch/interrupts.h>
#include <arch/serial.h>
#include <demos/compiler.h>

static void timer_handle_test(struct interrupt_frame *frame)
{
    (void)(frame);

    const char str[] = "non-implemented PIT interrupt\n";
    serial_write(0, str, sizeof(str) - 1);
}

void __noreturn early_init(void)
{
    init_serial(0, SERIAL_DEFAULT_RATE);
    init_interrupts();
    init_i8259();

    set_interrupt_handler(I8259_IRQ0, timer_handle_test);
    enable_interrupts();

    for(;;);
}
