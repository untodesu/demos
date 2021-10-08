#ifndef ARCH_INTERRUPTS_H
#define ARCH_INTERRUPTS_H 1
#include <arch/stdint.h>
#include <demos/cdefs.h>

struct interrupt_frame {
    uint32_t edi, esi, ebp, esp_u, ebx, edx, ecx, eax;
    uint32_t gs, fs, es, ds;
    uint32_t int_no;
    uint32_t error_code;
    uint32_t eip, cs, eflags;
    uint32_t esp, ss;
} __packed;

typedef void(*interrupt_handler_t)(struct interrupt_frame *frame);

int set_interrupt_handler(uint8_t int_no, interrupt_handler_t func);
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
