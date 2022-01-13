/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _X86_ST2_H_
#define _X86_ST2_H_ 1
#include <stivale2.h>

extern struct stivale2_struct st2;
const void *st2_find_tag(uint64_t identifier);

#endif
