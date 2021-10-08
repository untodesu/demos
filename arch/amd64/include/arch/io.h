#ifndef ARCH_IO_H
#define ARCH_IO_H 1
#include <arch/stdint.h>


static inline void outb(uint16_t p, uint8_t v)
{
    asm volatile("outb %0, %1"::"a"(v), "Nd"(p));
}

static inline void outw(uint16_t p, uint16_t v)
{
    asm volatile("outw %0, %1"::"a"(v), "Nd"(p));
}

static inline void outl(uint16_t p, uint32_t v)
{
    asm volatile("outl %0, %1"::"a"(v), "Nd"(p));
}

static inline uint8_t inb(uint16_t p)
{
    uint8_t v;
    asm volatile("inb %1, %0":"=a"(v):"Nd"(p));
    return v;
}

static inline uint16_t inw(uint16_t p)
{
    uint16_t v;
    asm volatile("inw %1, %0":"=a"(v):"Nd"(p));
    return v;
}

static inline uint32_t inl(uint16_t p)
{
    uint32_t v;
    asm volatile("inl %1, %0":"=a"(v):"Nd"(p));
    return v;
}

static inline void io_wait(void)
{
    // FIXME: should we zero AL? This most
    // definitely fucks something up...
    asm volatile("outb %0, $0x80"::"a"(0));
}

#endif
