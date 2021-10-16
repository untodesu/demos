#ifndef _ARCH_I8253_H_
#define _ARCH_I8253_H_ 1
#include <stddef.h>

#define I8253_SPEED 14551

void init_i8253(void);
size_t i8253_ticks(void);

#endif
