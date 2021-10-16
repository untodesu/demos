#ifndef _ARCH_I8259_H_
#define _ARCH_I8259_H_ 1
#include <inttypes.h>

#define I8259_IRQ(x) ((x) + 0x20)

void init_i8259(void);
void i8259_mask(unsigned int irq, int set);
int i8259_send_eoi(unsigned int irq);

#endif
