#include <arch/i8253.h>
#include <arch/i8259.h>
#include <arch/interrupts.h>
#include <arch/serial.h>
#include <demos/compiler.h>

void __noreturn early_init(void)
{
    init_serial(0, SERIAL_DEFAULT_RATE);
    init_interrupts();
    init_pic();
    init_pit();

    enable_interrupts();

    for(;;);
}
