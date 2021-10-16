#ifndef _TMVGA_H_
#define _TMVGA_H_ 1
#include <stddef.h>

struct stivale2_struct_tag_textmode;

int init_tmvga(const struct stivale2_struct_tag_textmode *tag);
void tmvga_write(const void *s, size_t n);

#endif
