#ifndef __DRIVERS_I8253_H__
#define __DRIVERS_I8253_H__ 1
#include <lib/inttypes.h>

#define I8253_SPEED 14551

void init_i8253(void);
uint64_t i8253_ticks(void);

#endif
