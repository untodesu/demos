#ifndef _ARCH_IO_H_
#define _ARCH_IO_H_ 1
#include <inttypes.h>

static inline void io_wait(void)
{
    asm volatile("outb %0, $0x80"::"a"(0));
}

#define _declare_inx(t, f)                                  \
    static inline t in##f(uint16_t p)                       \
    {                                                       \
        t v;                                                \
        asm volatile("in"#f" %1, %0":"=a"(v):"Nd"(p));      \
        return v;                                           \
    }

#define _declare_inxw(t, f)                                 \
    static inline t in##f##w(uint16_t p)                    \
    {                                                       \
        t v;                                                \
        asm volatile("in"#f" %1, %0":"=a"(v):"Nd"(p));      \
        io_wait();                                          \
        return v;                                           \
    }

#define _declare_outx(t, f)                                 \
    static inline void out##f(uint16_t p, t v)              \
    {                                                       \
        asm volatile("out"#f" %0, %1"::"a"(v), "Nd"(p));    \
    }

#define _declare_outxw(t, f)                                \
    static inline void out##f##w(uint16_t p, t v)           \
    {                                                       \
        asm volatile("out"#f" %0, %1"::"a"(v), "Nd"(p));    \
        io_wait();                                          \
    }

_declare_inx(uint8_t,       b)
_declare_inxw(uint8_t,      b)
_declare_outx(uint8_t,      b)
_declare_outxw(uint8_t,     b)

_declare_inx(uint16_t,      w)
_declare_inxw(uint16_t,     w)
_declare_outx(uint16_t,     w)
_declare_outxw(uint16_t,    w)

_declare_inx(uint32_t,      l)
_declare_inxw(uint32_t,     l)
_declare_outx(uint32_t,     l)
_declare_outxw(uint32_t,    l)

#endif
