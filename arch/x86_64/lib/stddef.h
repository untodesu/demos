#ifndef __LIB_STDDEF_H__
#define __LIB_STDDEF_H__ 1

#if !defined(NULL)
#define NULL ((void *)(0))
#endif

#if !defined(offsetof)
#define offsetof(s, m) ((size_t)(&((s *)NULL)->m))
#endif

#if !defined(SIZE_T_DEFINED)
#define SIZE_T_DEFINED 1
typedef unsigned long int size_t;
#endif

#if !defined(PTRDIFF_T_DEFINED)
#define PTRDIFF_T_DEFINED 1
typedef signed long int ptrdiff_t;
#endif

#endif
