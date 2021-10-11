#ifndef __SYS_KPRINTF_H__
#define __SYS_KPRINTF_H__ 1
#include <stdarg.h>
#include <stddef.h>
#include <sys/compiler.h>

typedef void(*kprintf_func_t)(const void *, size_t);

void set_kprintf_func(kprintf_func_t func);
void kprintf(const char *fmt, ...) __printf(1, 2);
void kvprintf(const char *fmt, va_list va);

#endif
