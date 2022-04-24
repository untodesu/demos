/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:14:08 */
#ifndef _SYS_INITCALL_H_
#define _SYS_INITCALL_H_ 1
#include <sys/cdefs.h>

/* Initcall function prototype */
typedef int(*initcall_t)(void);

/* A NULL-terminated list of initcall functions
 * sorted in a correct order to run on boot. */
extern const initcall_t initcalls[];

/* Link a C function to an initcall */
#define initcall(id, fn) \
    int __initcall_##id(void) __alias(fn)

/* Forward declare an initcall function. */
#define initcall_extern(id) \
    int __initcall_##id(void)

/* Declare an initcall dependency.
 * If an initcall depends on another, the other
 * one will be guaranteed to be called first. */
#define initcall_dependency(id, dp) \
    static const initcall_t __used __section(".discard.initcall.test") \
        __concat(__test_initcall, __COUNTER__) = &__initcall_##dp, \
        __concat(__test_initcall, __COUNTER__) = &__initcall_##id; \
    static const char __used __section(".discard.initcall.depend") __aligned(1) \
        __concat(__depend_initcall, __COUNTER__)[] = #dp " " #id

/* Pre-defined initcalls for the components to depend on. */
initcall_extern(tier_0);
initcall_extern(tier_1);
initcall_extern(tier_2);
initcall_extern(tier_3);

/* Declare a tier-0 initcall and link it to a function.
 * Tier-0 initcalls initialize very early platform-specific
 * components such as memory protection and interrupts. */
#define initcall_tier_0(id, fn) \
    initcall(id, fn); \
    initcall_dependency(id, tier_0); \
    initcall_dependency(tier_1, id)

/* Declare a tier-1 initcall and link it to a function.
 * Tier-1 initcalls initialize mostly still platform-specific
 * components but also some parts of portable code that needs
 * to be set up using a platform-specific dependency. */
#define initcall_tier_1(id, fn) \
    initcall(id, fn); \
    initcall_dependency(id, tier_1); \
    initcall_dependency(tier_2, id)

/* Declare a tier-2 initcall and link it to a function.
 * Tier-2 initcalls initialize mostly portable components
 * and rarely platform-specific things. At this point the
 * kernel initializes some basic I/O drivers. */
#define initcall_tier_2(id, fn) \
    initcall(id, fn); \
    initcall_dependency(id, tier_2); \
    initcall_dependency(tier_3, id)

/* Declare a tier-3 initcall and link it to a function.
 * Tier-3 initcalls are the last to get called and they
 * initialize only portable code: loading modules, mounting
 * devices, setting up more complex device drivers, etc. */
#define initcall_tier_3(id, fn) \
    initcall(id, fn); \
    initcall_dependency(id, tier_3)

#endif
