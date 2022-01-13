/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _X86_I8253_H_
#define _X86_I8253_H_ 1
#include <sys/init.h>
#include <stddef.h>

#define I8253_SPEED 14551
size_t i8253_ticks(void);

initcall_extr(i8253);

#endif
