#ifndef _SPRINTF_H_
#define _SPRINTF_H_ 1
#include <sys/compiler.h>
#include <stdarg.h>
#include <stddef.h>

int sprintf(char *s, const char *fmt, ...) __printf(2, 3);
int vsprintf(char *s, const char *fmt, va_list va);
int snprintf(char *s, size_t n, const char *fmt, ...) __printf(3, 4);
int vsnprintf(char *s, size_t n, const char *fmt, va_list va);

#endif
