/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:14:42 */
#ifndef _STDDEF_H_
#define _STDDEF_H_ 1

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_ 1
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef _SSIZE_T_DEFINED_
#define _SSIZE_T_DEFINED_ 1
typedef signed long ssize_t;
#endif

#ifndef _PTRDIFF_T_DEFINED_
#define _PTRDIFF_T_DEFINED_ 1
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif

#if 0 /* not now */
#ifndef _WCHAR_T_DEFINED_
#define _WCHAR_T_DEFINED_ 1
typedef __WCHAR_TYPE__ wchar_t;
#endif
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef offsetof
#define offsetof(t, m) __builtin_offsetof(t, m)
#endif

#endif
