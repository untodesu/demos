#ifndef __SYS_DRIVERS_CONSOLE_STIVALECON_H__
#define __SYS_DRIVERS_CONSOLE_STIVALECON_H__ 1
#include <lib/stddef.h>

struct stivale2_struct_tag_terminal;

int init_stivalecon(const struct stivale2_struct_tag_terminal *tag);
void stivalecon_write(const void *s, size_t n);

#endif
