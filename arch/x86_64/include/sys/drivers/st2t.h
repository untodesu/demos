#ifndef __SYS_DRIVERS_ST2T_H__
#define __SYS_DRIVERS_ST2T_H__ 1
#include <stddef.h>

int init_st2t(const void *tag);
void st2t_write(const void *s, size_t n);

#endif
