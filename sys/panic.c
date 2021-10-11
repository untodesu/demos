#include <lib/sprintf.h>
#include <sys/interrupts.h>
#include <sys/kprintf.h>
#include <sys/panic.h>

static char panic_buffer[512] = { 0 };

void __noreturn panic(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vsnprintf(panic_buffer, sizeof(panic_buffer), fmt, va);
    va_end(va);
    kprintf("panic: %s", panic_buffer);
    for(;;);
}
