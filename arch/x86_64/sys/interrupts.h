#ifndef __SYS_INTERRUPTS_H__
#define __SYS_INTERRUPTS_H__ 1
#include <lib/compiler.h>
#include <lib/inttypes.h>

struct interrupt_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t vector, error;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

typedef void(*interrupt_handler_t)(struct interrupt_frame *);

void set_interrupt_handler(unsigned int vector, interrupt_handler_t handler);
void init_interrupts(void);

static inline void disable_interrupts(void)
{
    asm volatile("cli");
}

static inline void enable_interrupts(void)
{
    asm volatile("sti");
}

#endif
