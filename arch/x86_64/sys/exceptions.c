#include <lib/compiler.h>
#include <sys/exceptions.h>
#include <sys/interrupts.h>

/* arch/x86_64/sys/exceptions_trampoline.S */
extern void exception_00(void);
extern void exception_01(void);
extern void exception_02(void);
extern void exception_03(void);
extern void exception_04(void);
extern void exception_05(void);
extern void exception_06(void);
extern void exception_07(void);
extern void exception_08(void);
extern void exception_09(void);
extern void exception_0A(void);
extern void exception_0B(void);
extern void exception_0C(void);
extern void exception_0D(void);
extern void exception_0E(void);
extern void exception_0F(void);
extern void exception_10(void);
extern void exception_11(void);
extern void exception_12(void);
extern void exception_13(void);
extern void exception_14(void);
extern void exception_15(void);
extern void exception_16(void);
extern void exception_17(void);
extern void exception_18(void);
extern void exception_19(void);
extern void exception_1A(void);
extern void exception_1B(void);
extern void exception_1C(void);
extern void exception_1D(void);
extern void exception_1E(void);
extern void exception_1F(void);

static exception_handler_t handlers[32] = { 0 };

void __used exception_handler(uint64_t vector, uint64_t code)
{
    if(!handlers[vector & 0x1F])
        return;
    handlers[vector & 0x1F](code);
}

void init_exceptions(void)
{
    set_interrupt_handler(0x00, (uintptr_t)(&exception_00), 0);
    set_interrupt_handler(0x01, (uintptr_t)(&exception_01), 0);
    set_interrupt_handler(0x02, (uintptr_t)(&exception_02), 0);
    set_interrupt_handler(0x03, (uintptr_t)(&exception_03), 0);
    set_interrupt_handler(0x04, (uintptr_t)(&exception_04), 0);
    set_interrupt_handler(0x05, (uintptr_t)(&exception_05), 0);
    set_interrupt_handler(0x06, (uintptr_t)(&exception_06), 0);
    set_interrupt_handler(0x07, (uintptr_t)(&exception_07), 0);
    set_interrupt_handler(0x08, (uintptr_t)(&exception_08), 0);
    set_interrupt_handler(0x09, (uintptr_t)(&exception_09), 0);
    set_interrupt_handler(0x0A, (uintptr_t)(&exception_0A), 0);
    set_interrupt_handler(0x0B, (uintptr_t)(&exception_0B), 0);
    set_interrupt_handler(0x0C, (uintptr_t)(&exception_0C), 0);
    set_interrupt_handler(0x0D, (uintptr_t)(&exception_0D), 0);
    set_interrupt_handler(0x0E, (uintptr_t)(&exception_0E), 0);
    set_interrupt_handler(0x0F, (uintptr_t)(&exception_0F), 0);
    set_interrupt_handler(0x10, (uintptr_t)(&exception_10), 0);
    set_interrupt_handler(0x11, (uintptr_t)(&exception_11), 0);
    set_interrupt_handler(0x12, (uintptr_t)(&exception_12), 0);
    set_interrupt_handler(0x13, (uintptr_t)(&exception_13), 0);
    set_interrupt_handler(0x14, (uintptr_t)(&exception_14), 0);
    set_interrupt_handler(0x15, (uintptr_t)(&exception_15), 0);
    set_interrupt_handler(0x16, (uintptr_t)(&exception_16), 0);
    set_interrupt_handler(0x17, (uintptr_t)(&exception_17), 0);
    set_interrupt_handler(0x18, (uintptr_t)(&exception_18), 0);
    set_interrupt_handler(0x19, (uintptr_t)(&exception_19), 0);
    set_interrupt_handler(0x1A, (uintptr_t)(&exception_1A), 0);
    set_interrupt_handler(0x1B, (uintptr_t)(&exception_1B), 0);
    set_interrupt_handler(0x1C, (uintptr_t)(&exception_1C), 0);
    set_interrupt_handler(0x1D, (uintptr_t)(&exception_1D), 0);
    set_interrupt_handler(0x1E, (uintptr_t)(&exception_1E), 0);
    set_interrupt_handler(0x1F, (uintptr_t)(&exception_1F), 0);
}

void set_exception_handler(unsigned int vector, exception_handler_t handler)
{
    handlers[vector & 0x1F] = handler;
}
