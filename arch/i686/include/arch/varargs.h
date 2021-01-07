#ifndef __ARCH_VARARGS_H__
#define __ARCH_VARARGS_H__ 1

typedef unsigned char * __arch_va_list;
#define __arch_va_start(va, x)  ((va) = (va_list)(&(x) + 1))
#define __arch_va_arg(va, type) ((type *)((va) += sizeof(type)))[-1]
#define __arch_va_end(va)       ((va) = 0)

#endif
