/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_PANIC_H_
#define _SYS_PANIC_H_ 1
#include <sys/cdefs.h>
void __noreturn panic(const char *fmt, ...);
#endif
