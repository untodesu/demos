#ifndef __DEMOS_COMPILER_H__
#define __DEMOS_COMPILER_H__ 1

#define __always_inline __attribute__((always_inline))
#define __deprecated    __attribute__((deprecated))
#define __noinline      __attribute__((noinline))
#define __noreturn      __attribute__((noreturn))
#define __optimize(x)   __attribute__((optimize(x)))
#define __packed        __attribute__((packed))
#define __printf(x, y)  __attribute__((format(printf, x, y)))
#define __pure          __attribute__((pure))
#define __weak          __attribute__((weak))

#endif
