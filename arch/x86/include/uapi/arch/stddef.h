#ifndef UAPI_ARCH_STDDEF_H
#define UAPI_ARCH_STDDEF_H 1

#define __demos_NULL ((void *)(0))
#define __demos_offsetof(s, m) ((size_t)(&((s *)__demos_NULL)->m))

#if defined(X86_64)
typedef unsigned long long __demos_size_t;
typedef signed long long __demos_ptrdiff_t;
#else
typedef unsigned int __demos_size_t;
typedef signed int __demos_ptrdiff_t;
#endif

#endif
