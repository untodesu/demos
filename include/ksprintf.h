/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:14:20 */
#ifndef _KSPRINTF_H_
#define _KSPRINTF_H_ 1
#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

size_t ksprintf(char *s, const char *fmt, ...) __format(printf, 2, 3);
size_t kvsprintf(char *s, const char *fmt, va_list va);
size_t ksnprintf(char *s, size_t n, const char *fmt, ...) __format(printf, 3, 4);
size_t kvsnprintf(char *s, size_t n, const char *fmt, va_list va);

#endif
