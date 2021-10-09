#ifndef ARCH_DRIVERS_I8259_H
#define ARCH_DRIVERS_I8259_H 1
#include <arch/stdint.h>
#include <stdbool.h>

#define I8259_IRQ0  (0x20)
#define I8259_IRQ8  (0x28)
#define I8259_IRQ15 (0x2F)

void init_i8259(void);
void i8259_mask(uint8_t irq_no, bool set);
void i8259_eoi(uint8_t irq_no);
bool get_i8259_irq(uint8_t int_no, uint8_t *irq_no);

#endif
