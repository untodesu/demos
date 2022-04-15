/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_CPU_H_
#define _SYS_CPU_H_ 1
#include <sys/cdefs.h>

static inline void disable_interrupts(void)
{
    asm volatile("cli");
}

static inline void enable_interrupts(void)
{
    asm volatile("sti");
}

static inline void cpu_halt(void)
{
    asm volatile("hlt");
}

static inline void __noreturn cpu_brick(void)
{
    for(;;) {
        disable_interrupts();
        cpu_halt();
    }
}

#endif
