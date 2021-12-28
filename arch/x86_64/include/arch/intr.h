#ifndef _ARCH_INTR_H_
#define _ARCH_INTR_H_ 1
#include <arch/cpu.h>

typedef void(*interrupt_handler_t)(struct interrupt_frame *);
void set_interrupt_handler(unsigned int vector, interrupt_handler_t handler);
void init_interrupts(void);

#endif
