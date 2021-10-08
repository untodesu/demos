#ifndef ARCH_SERIAL_H
#define ARCH_SERIAL_H 1
#include <arch/stddef.h>

#define SERIAL0 0
#define SERIAL1 1
#define SERIAL2 2
#define SERIAL3 3

int init_serial(int id, unsigned int rate);
void serial_write(int id, const void *s, size_t n);

#endif
