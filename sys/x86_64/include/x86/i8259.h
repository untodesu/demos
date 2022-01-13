/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _X86_I8259_H_
#define _X86_I8259_H_ 1
#include <sys/init.h>
#include <stdint.h>

#define I8259_IRQ(x) ((x) + 0x20)

void i8259_mask(unsigned int irq, int set);
int i8259_send_eoi(unsigned int irq);

initcall_extr(i8259);

#endif
