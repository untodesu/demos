#ifndef __DRIVERS_VGACON_H__
#define __DRIVERS_VGACON_H__ 1
#include <lib/stddef.h>

struct stivale2_struct_tag_textmode;

int init_vgacon(const struct stivale2_struct_tag_textmode *tag);
void vgacon_write(const void *s, size_t n);

#endif
