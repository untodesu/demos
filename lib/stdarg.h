#ifndef __LIB_STDARG_H__
#define __LIB_STDARG_H__ 1

typedef __builtin_va_list va_list;
#define va_start(va, x) __builtin_va_start(va, x)
#define va_copy(va, dv) __builtin_va_copy(va, dv)
#define va_arg(va, t)   __builtin_va_arg(va, t)
#define va_end(va)      __builtin_va_end(va)

#endif
