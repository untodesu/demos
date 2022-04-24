/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sun Apr 24 2022 17:15:03 */
#ifndef _SYS_CPU_H_
#define _SYS_CPU_H_ 1
#include <stdint.h>
#include <sys/cdefs.h>

typedef uint64_t cpu_flags_t;

static inline cpu_flags_t get_cpu_flags(void)
{
    cpu_flags_t flags;
    asm volatile("pushfq; popq %0":"=a"(flags));
    return flags;
}

static inline void set_cpu_flags(cpu_flags_t flags)
{
    asm volatile("pushq %0; popfq"::"a"(flags));
}

static inline void halt_cpu(void)
{
    asm volatile("hlt");
}

#endif
