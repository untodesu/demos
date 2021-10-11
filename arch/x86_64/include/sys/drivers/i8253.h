#ifndef __SYS_DRIVERS_I8253_H__
#define __SYS_DRIVERS_I8253_H__ 1
#include <inttypes.h>

#define I8253_SPEED 14551

void init_i8253(void);
uint64_t i8253_ticks(void);

#endif
