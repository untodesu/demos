/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_DEBUG_H_
#define _SYS_DEBUG_H_ 1
#include <stdarg.h>
#include <sys/cdefs.h>

void __noreturn panicv(const char *fmt, va_list va);
void __noreturn panic(const char *fmt, ...) __format(printf, 1, 2);

#define panic_unless(x) \
    do { if(__unlikely(!(x))) { \
    panic("%s:%u: %s", __BASE_FILE__, __LINE__, #x); \
    }} while(0)

#define panic_unless_msg(x, fmt, ...) \
    do { if(__unlikely(!(x))) { \
    panic((fmt), ##__VA_ARGS__); \
    }} while(0)

#endif
