#include <lib/sprintf.h>
#include <sys/interrupts.h>
#include <sys/klog.h>
#include <sys/panic.h>

void __noreturn panic(const char *fmt, ...)
{
    char buffer[512] = { 0 };

    disable_interrupts();

    va_list va;
    va_start(va, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    klog(KLOG_FATAL, "kernel panic: %s", buffer);

    for(;;);
}
