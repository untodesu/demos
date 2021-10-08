#ifndef UAPI_ARCH_STDARG_H
#define UAPI_ARCH_STDARG_H 1

typedef __builtin_va_list __demos_va_list;
#define __demos_va_start(va, x) __builtin_va_start(va, x)
#define __demos_va_copy(va, dv) __builtin_va_copy(va, dv)
#define __demos_va_arg(va, t)   __builtin_va_arg(va, t)
#define __demos_va_end(va)      __builtin_va_end(va)

#endif
