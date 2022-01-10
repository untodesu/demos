#ifndef _STDDEF_H_
#define _STDDEF_H_ 1

#define NULL ((void *)(0))
#define offsetof(s, m) ((size_t)(&((s *)NULL)->m))
typedef unsigned long int size_t;
typedef signed long int ptrdiff_t;

#endif
