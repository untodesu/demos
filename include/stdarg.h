/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _STDARG_H_
#define _STDARG_H_ 1

typedef __builtin_va_list va_list;
#define va_start(va, x) __builtin_va_start(va, x)
#define va_copy(va, dv) __builtin_va_copy(va, dv)
#define va_arg(va, t)   __builtin_va_arg(va, t)
#define va_end(va)      __builtin_va_end(va)

#endif
