#ifndef ARCH_STDDEF_H
#define ARCH_STDDEF_H 1
#include <uapi/arch/stddef.h>

#if !defined(NULL)
#define NULL __demos_NULL
#endif

#if !defined(offsetof)
#define offsetof(s, m) __demos_offsetof(s, m)
#endif

#if !defined(SIZE_T_DEFINED)
#define SIZE_T_DEFINED 1
typedef __demos_size_t size_t;
#endif

#if !defined(PTRDIFF_T_DEFINED)
#define PTRDIFF_T_DEFINED 1
typedef __demos_ptrdiff_t ptrdiff_t;
#endif

#endif
