/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _STDDEF_H_
#define _STDDEF_H_ 1
#define NULL ((void *)0)
#define offsetof(t, m) __builtin_offsetof(t, m)
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __WCHAR_TYPE__ wchar_t;
#endif
