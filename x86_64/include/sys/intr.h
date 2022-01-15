/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_INTR_H_
#define _SYS_INTR_H_ 1
#include <sys/cpu.h>
#include <sys/initcall.h>
#include <stdint.h>

struct interrupt_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t vector, error;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

typedef void (*interrupt_t)(struct interrupt_frame *, void *);

#define disable_interrupts() cpu_cli()
#define enable_interrupts() cpu_sti()
void set_interrupt_handler(unsigned int vector, interrupt_t func, void *data);

initcall_extern(interrupts);

#endif
