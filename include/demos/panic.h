#ifndef _DEMOS_PANIC_H_
#define _DEMOS_PANIC_H_ 1
#include <demos/compiler.h>

void __noreturn panic(const char *fmt, ...);

#endif
