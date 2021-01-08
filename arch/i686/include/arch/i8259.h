#ifndef __ARCH_I8259_H__
#define __ARCH_I8259_H__ 1
#include <arch/types.h>

#define PIC_IRQ0  0x20
#define PIC_IRQ8  0x28
#define PIC_IRQ15 0x2F

void init_pic(void);

void pic_mask_irq(uint8_t irq_no);
void pic_unmask_irq(uint8_t irq_no);

void pic_send_eoi(uint8_t irq_no);

#endif
