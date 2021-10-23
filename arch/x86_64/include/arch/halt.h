#ifndef _ARCH_HALT_H_
#define _ARCH_HALT_H_ 1
#include <demos/compiler.h>

static inline void __noreturn arch_halt(void)
{
    for(;;) {
        asm volatile("cli");
        asm volatile("hlt");
    }
}

#endif
