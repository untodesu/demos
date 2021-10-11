#ifndef __SYS_PANIC_H__
#define __SYS_PANIC_H__ 1
#include <lib/compiler.h>

void __noreturn panic(const char *fmt, ...);

#endif
