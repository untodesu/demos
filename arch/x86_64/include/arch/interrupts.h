#ifndef ARCH_INTERRUPTS_H
#define ARCH_INTERRUPTS_H 1
#include <arch/stdint.h>
#include <demos/cdefs.h>

struct interrupt_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t int_no;
    uint64_t error_code;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

typedef void(*interrupt_handler_t)(struct interrupt_frame *);

void set_interrupt_handler(uint8_t int_no, interrupt_handler_t handler);
void init_interrupts(void);

static inline void enable_interrupts(void)
{
    asm volatile("sti");
}

static inline void disable_interrupts(void)
{
    asm volatile("cli");
}

#endif
