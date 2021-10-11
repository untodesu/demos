#ifndef __SYS_INTERRUPTS_H__
#define __SYS_INTERRUPTS_H__ 1
#include <lib/compiler.h>
#include <lib/inttypes.h>

struct interrupt_frame {
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

void init_interrupts(void);
void set_interrupt_handler(unsigned int vector, uintptr_t offset, int level);
static inline void disable_interrupts(void) { asm volatile("cli"); }
static inline void enable_interrupts(void) { asm volatile("sti"); }

#endif
