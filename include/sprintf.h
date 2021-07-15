#ifndef SPRINTF_H
#define SPRINTF_H 1
#include <arch/stdarg.h>
#include <arch/stddef.h>
#include <demos/cdefs.h>

int sprintf(char *s, const char *fmt, ...) __printf(2, 3);
int vsprintf(char *s, const char *fmt, va_list va);
int snprintf(char *s, size_t n, const char *fmt, ...) __printf(3, 4);
int vsnprintf(char *s, size_t n, const char *fmt, va_list va);

#endif
