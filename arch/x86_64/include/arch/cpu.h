#ifndef _ARCH_CPU_H_
#define _ARCH_CPU_H_ 1
#include <demos/compiler.h>
#include <inttypes.h>

struct interrupt_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t vector, error;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

static inline void __noreturn cpu_brick(void)
{
    for(;;) {
        asm volatile("cli");
        asm volatile("hlt");
    }
}

static inline void cpu_disable_interrupts(void)
{
    asm volatile("cli");
}

static inline void cpu_enable_interrupts(void)
{
    asm volatile("sti");
}

#endif
