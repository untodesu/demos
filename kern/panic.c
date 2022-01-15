/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/cpu.h>
#include <sys/printk.h>
#include <sys/sprintf.h>
#include <sys/panic.h>

void __noreturn panic(const char *fmt, ...)
{
    va_list va;
    char msg[CONFIG_PRINTK_MESSAGE_SIZE] = { 0 };

    va_start(va, fmt);
    vsnprintf(msg, sizeof(msg), fmt, va);
    va_end(va);

    printk(LOGLEVEL_EMERG, "kernel panic: %s", msg);

    cpu_brick();
}
