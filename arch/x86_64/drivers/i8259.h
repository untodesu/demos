#ifndef __DRIVERS_I8259_H__
#define __DRIVERS_I8259_H__ 1
#include <lib/inttypes.h>

#define I8259_IRQ(x) ((x) + 0x20)

void init_i8259(void);
void i8259_mask(unsigned int irq, int set);
void i8259_send_eoi(unsigned int irq);

#endif
