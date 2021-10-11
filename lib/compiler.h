#ifndef __LIB_COMPILER_H__
#define __LIB_COMPILER_H__ 1

#define __aligned(x)    __attribute__((aligned(x)))
#define __deprecated    __attribute__((deprecated))
#define __interrupt     __attribute__((interrupt))
#define __optimize(x)   __attribute__((optimize(x)))
#define __packed        __attribute__((packed))
#define __printf(x, y)  __attribute__((format(printf, x, y)))
#define __unused        __attribute__((unused))
#define __used          __attribute__((used))
#define __section(x)    __attribute__((section(x)))
#define __noreturn      __attribute__((noreturn))

#endif
