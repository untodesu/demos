#ifndef ARCH_INTERRUPTS_H
#define ARCH_INTERRUPTS_H 1
#include <arch/stdint.h>
#include <demos/cdefs.h>
#include <stdbool.h>

struct interrupt_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t int_no;
    uint64_t error_code;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

typedef void(*interrupt_handler_t)(struct interrupt_frame *);

bool set_interrupt_handler(uint8_t int_no, interrupt_handler_t handler);
void init_interrupts(void);
#define disable_interrupts() asm volatile("cli")
#define enable_interrupts() asm volatile("sti")

#endif
