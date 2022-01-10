/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_KM_H_
#define _SYS_KM_H_ 1
#include <stddef.h>

void *kmalloc(size_t n);
void kmfree(void *s);

#endif
