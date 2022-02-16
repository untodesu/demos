/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _X86_I8259_H_
#define _X86_I8259_H_ 1
#include <sys/interrupts.h>
#include <sys/initcall.h>

#define I8259_IRQ_BASE      0x20
#define I8259_IRQ_LIMIT     0x30
#define I8259_IRQ_CHIP1_OFF 0x00
#define I8259_IRQ_CHIP2_OFF 0x08
#define I8250_IRQ_COUNT     0x10

#define I8259_IRQ_I8253     0x00
#define I8259_IRQ_KEYBOARD  0x01
#define I8259_IRQ_CHIP2     0x02
#define I8259_IRQ_SERIAL1   0x03
#define I8259_IRQ_SERIAL0   0x04
#define I8259_IRQ_PARALLEL1 0x05
#define I8259_IRQ_FLOPPY    0x06
#define I8259_IRQ_PARALLEL0 0x07
#define I8259_IRQ_RTC       0x08
#define I8259_IRQ_09        0x09
#define I8259_IRQ_0A        0x0A
#define I8259_IRQ_0B        0x0B
#define I8259_IRQ_MOUSE     0x0C
#define I8259_IRQ_X87       0x0D
#define I8259_IRQ_ATA0      0x0E
#define I8259_IRQ_ATA1      0x0F

void i8259_disable_irqs(void);
void i8259_enable_irqs(void);
void i8259_mask_irq(unsigned int irqvector);
void i8259_unmask_irq(unsigned int irqvector);
int i8259_set_irq_handler(unsigned int irqvector, interrupt_t func, void *data);

initcall_extern(i8259);

#endif
