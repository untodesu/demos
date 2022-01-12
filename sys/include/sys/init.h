/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_INIT_H_
#define _SYS_INIT_H_ 1
#include <sys/cdefs.h>

typedef int (*initcall_t)(void);

#define extern_initcall(id) \
    int __initcall_##id(void)

#define declare_initcall(id, fn) \
    int __initcall_##id(void) __alias(fn)

#define initcall_dependency(id, dp) \
    static initcall_t __used __section(".discard.initcalls.chk") \
        __concat(__chk_initcall, __COUNTER__) = &__initcall_##dp, \
        __concat(__chk_initcall, __COUNTER__) = &__initcall_##id; \
    static const char __used __section(".discard.initcalls.dep") __aligned(1) \
        __concat(__dep_initcall, __COUNTER__)[] = #dp " " #id

#define early_initcall(id, fn) \
    declare_initcall(id, fn); \
    initcall_dependency(id, early); \
    initcall_dependency(kernel, id)

#define kernel_initcall(id, fn) \
    declare_initcall(id, fn); \
    initcall_dependency(id, kernel)

extern_initcall(early);
extern_initcall(kernel);

extern const initcall_t initcalls[];

#endif
