#include <arch/halt.h>
#include <demos/klog.h>
#include <demos/panic.h>
#include <sprintf.h>

void __noreturn panic(const char *fmt, ...)
{
    char buffer[512] = { 0 };

    va_list va;
    va_start(va, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    klog(KLOG_FATAL, "kernel panic: %s", buffer);

    arch_halt();
}
