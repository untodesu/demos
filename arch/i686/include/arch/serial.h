#ifndef __ARCH_SERIAL_H__
#define __ARCH_SERIAL_H__ 1
#include <arch/types.h>

#define SERIAL_DEFAULT_RATE 9600

int serial_init(int id, unsigned int speed);
void serial_write(int id, const void *s, size_t n);

#endif
