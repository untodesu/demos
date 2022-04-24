/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:14:03 */
#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_ 1

/* Common macros */
#define __stringify1(x) #x
#define __stringify(x) __stringify1(x)
#define __mark_used(x) ((void)(x))
#define __concat1(x, y) x##y
#define __concat(x, y) __concat1(x, y)

/* Hacks to shut vscode up */
#if __STDC_VERSION__ >= 199901L
#define restrict __restrict__
#elif defined(__cplusplus)
#define restrict
#endif

/* GNU C attributes */
#define __alias(x) __attribute__((alias(#x)))
#define __aligned(x) __attribute__((aligned(x)))
#define __deprecated(x) __attribute__((deprecated(x)))
#define __format(x, y, z) __attribute__((format(x, y, z)))
#define __likely(x) (__builtin_expect(!!(x), 1))
#define __noreturn __attribute__((noreturn))
#define __optimize(x) __attribute__((optimize(x)))
#define __packed __attribute__((packed))
#define __section(x) __attribute__((section(x)))
#define __unlikely(x) (__builtin_expect(!!(x), 0))
#ifndef __unused
    #define __unused __attribute__((unused))
#endif
#define __used __attribute__((used))

/* Hacks */
#define __align_ceil(x, align) (((x) + (align) - 1) & ~((align) - 1))
#define __align_floor(x, align) ((x) & ~((align) - 1))

#endif
