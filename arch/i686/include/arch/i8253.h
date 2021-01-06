#ifndef __ARCH_I8253_H__
#define __ARCH_I8253_H__ 1
#include <arch/types.h>

#define PIT_TPS 14551

void init_pit(void);
uint64_t pit_get_ticks(void);

#endif
