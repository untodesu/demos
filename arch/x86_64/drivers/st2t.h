#ifndef __SYS_DRIVERS_ST2T_H__
#define __SYS_DRIVERS_ST2T_H__ 1
#include <lib/stddef.h>

struct stivale2_struct_tag_terminal;

int init_st2t(const struct stivale2_struct_tag_terminal *tag);
void st2t_write(const void *s, size_t n);

#endif
