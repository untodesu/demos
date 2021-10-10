#ifndef ARCH_DRIVERS_I8253_H
#define ARCH_DRIVERS_I8253_H 1
#include <arch/stdint.h>

#define I8253_SPEED 14551

void init_i8253(void);
uint64_t i8253_ticks(void);

#endif
