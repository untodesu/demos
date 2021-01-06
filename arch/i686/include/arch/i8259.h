#ifndef __ARCH_I8259_H__
#define __ARCH_I8259_H__ 1
#include <arch/types.h>

#define I8259_IRQ0  0x20
#define I8259_IRQ8  0x28
#define I8259_IRQ15 0x2F

void init_i8259(void);

void i8259_mask_irq(uint8_t irq_no);
void i8259_unmask_irq(uint8_t irq_no);

void i8259_send_eoi(uint8_t irq_no);

#endif
