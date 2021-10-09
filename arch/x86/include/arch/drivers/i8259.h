#ifndef ARCH_I8259_H
#define ARCH_I8259_H 1
#include <arch/stdint.h>

#define I8259_IRQ0  (0x20)
#define I8259_IRQ8  (0x28)
#define I8259_IRQ15 (0x2F)

void init_i8259(void);
void i8259_mask(uint8_t irq);
void i8259_unmask(uint8_t irq);
void i8259_eoi(uint8_t irq);

#endif
