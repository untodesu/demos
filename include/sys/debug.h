/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sun Apr 24 2022 00:13:11 */
#ifndef _SYS_DEBUG_H_
#define _SYS_DEBUG_H_ 1
#include <stdarg.h>
#include <sys/cdefs.h>

void panicv(const char *fmt, va_list va) __noreturn;
void panic(const char *fmt, ...) __noreturn __format(printf, 1, 2);

#define panic_unless(x) \
    do { if(__unlikely(!(x))) { \
    panic("%s:%u: %s", __BASE_FILE__, __LINE__, #x); \
    }} while(0)

#define panic_unless_msg(x, fmt, ...) \
    do { if(__unlikely(!(x))) { \
    panic((fmt), ##__VA_ARGS__); \
    }} while(0)

#endif
