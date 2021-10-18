#ifndef _DEMOS_KMALLOC_H_
#define _DEMOS_KMALLOC_H_ 1
#include <stddef.h>

void *kmalloc(size_t n);
void kmfree(void *s);

#endif
