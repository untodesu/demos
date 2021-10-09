#ifndef ARCH_DRIVERS_ST2T_H
#define ARCH_DRIVERS_ST2T_H 1
#include <arch/stddef.h>
#include <stdbool.h>

bool init_st2t(const void *tag);
void st2t_write(const void *s, size_t n);

#endif
