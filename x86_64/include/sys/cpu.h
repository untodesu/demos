/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_CPU_H_
#define _SYS_CPU_H_ 1
#include <sys/cdefs.h>

static inline void cpu_cli(void)
{
    asm volatile("cli");
}

static inline void cpu_sti(void)
{
    asm volatile("sti");
}

static inline void __noreturn cpu_brick(void)
{
    for(;;) {
        asm volatile("cli");
        asm volatile("hlt");
    }
}

#endif
