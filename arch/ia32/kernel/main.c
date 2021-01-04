#include <arch/address.h>
#include <arch/types.h>
#include <demos/compiler.h>

void __noreturn arch_main(void)
{
    volatile uint16_t *vid = (uint16_t *)P2V(0xB8000);
    vid[0] = 'E' | 0x0F00;

    for(;;);
}
