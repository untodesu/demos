#include <arch/serial.h>
#include <demos/compiler.h>

void __noreturn early_init(void)
{
    if(serial_init(0, SERIAL_DEFAULT_RATE)) {
        // still funny
        const char str[] = "LUNCH TIME MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n";
        serial_write(0, str, sizeof(str) - 1);
    }

    for(;;);
}
