#ifndef ARCH_STDARG_H
#define ARCH_STDARG_H 1
#include <uapi/arch/stdarg.h>

typedef __demos_va_list va_list;
#define va_start(va, x) __demos_va_start(va, x)
#define va_copy(va, dv) __demos_va_copy(va, dv)
#define va_arg(va, t)   __demos_va_arg(va, t)
#define va_end(va)      __demos_va_end(va)

#endif
