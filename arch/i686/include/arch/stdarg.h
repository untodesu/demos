#ifndef __ARCH_STDARG_H__
#define __ARCH_STDARG_H__ 1

typedef unsigned char * va_list;
#define va_start(va, x)     ((va) = (va_list)(&(x) + 1))
#define va_arg(va, type)    ((type *)((va) += sizeof(type)))[-1]
#define va_end(va)          ((va) = 0)

#endif
