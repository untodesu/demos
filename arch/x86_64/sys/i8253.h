#ifndef __SYS_I8253_H__
#define __SYS_I8253_H__ 1
#include <lib/stddef.h>

#define I8253_SPEED 14551

void init_i8253(void);
size_t i8253_ticks(void);

#endif
