#ifndef __STDARG_H__
#define __STDARG_H__ 1
#include <arch/varargs.h>

typedef __arch_va_list va_list;
#define va_start(ap, x)     __arch_va_start(ap, x)
#define va_arg(ap, type)    __arch_va_arg(ap, type)
#define va_end(ap)          __arch_va_end(ap)

#endif
