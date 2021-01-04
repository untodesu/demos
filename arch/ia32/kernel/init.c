#include <arch/serial.h>
#include <demos/compiler.h>

void __noreturn early_init(void)
{
    if(serial_init()) {
        // funny
        const char str[] = "LUNCH TIME MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n";
        serial_write(str, sizeof(str) - 1);
    }

    for(;;);
}
