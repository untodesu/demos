#ifndef __ARCH_SERIAL_H__
#define __ARCH_SERIAL_H__ 1
#include <arch/types.h>

int serial_init(void);
void serial_write(const void *s, size_t n);

#endif
