/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sun Apr 24 2022 01:00:42 */
#ifndef _ARCH_INTR_H_
#define _ARCH_INTR_H_ 1
#include <sys/cdefs.h>
#include <sys/cpu.h>
#include <sys/initcall.h>

struct intr_frame {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t vector, error;
    uint64_t rip, cs, rflags;
    uint64_t rsp, ss;
} __packed;

typedef void(*intr_handler_t)(struct intr_frame *, void *);

cpu_flags_t enable_intrs(void);
cpu_flags_t disable_intrs(void);
void set_intr(unsigned int intr, intr_handler_t fn, void *arg);

initcall_extern(intr);

#endif
