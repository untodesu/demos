/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_INTR_H_
#define _SYS_INTR_H_ 1
#include <sys/initcall.h>
#include <stdint.h>

struct intr_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t vector, error;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

typedef void (*intr_handler_t)(struct intr_frame *, void *);

#define disable_intrs() asm volatile("cli")
#define enable_intrs() asm volatile("sti")
#define wait_for_intrs() asm volatile("hlt")
void set_intr_handler(unsigned int vector, intr_handler_t func, void *data);

initcall_extern(intrs);

#endif
