/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_INTERRUPT_H_
#define _SYS_INTERRUPT_H_ 1
#include <sys/cpu.h>
#include <sys/init.h>

typedef void(*interrupt_handler_t)(struct interrupt_frame *);
void set_interrupt_handler(unsigned int vector, interrupt_handler_t handler);

initcall_extr(interrupt);

#endif
