#ifndef DEMOS_KPRINTF_H
#define DEMOS_KPRINTF_H 1
#include <arch/stdarg.h>
#include <arch/stddef.h>
#include <demos/cdefs.h>

typedef void(*kprintf_func_t)(const void *, size_t);

void set_kprintf_func(kprintf_func_t func);
void kprintf(const char *fmt, ...) __printf(1, 2);
void kvprintf(const char *fmt, va_list va);

#endif
