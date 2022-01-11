/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/cpu.h>
#include <sys/klog.h>
#include <sys/ksprintf.h>
#include <sys/panic.h>

void __noreturn panic(const char *fmt, ...)
{
    char buffer[512] = { 0 };

    va_list va;
    va_start(va, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, va);
    va_end(va);

    klog(KLOG_FTL, "kernel panic: %s", buffer);

    cpu_brick();
}
