/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/debug.h>
#include <sys/printk.h>
#include <sys/sprintf.h>

void __noreturn panicv(const char *fmt, va_list va)
{
    static char msg[CONFIG_PRINTK_MSG_SIZE] = { 0 };
    vsnprintf(msg, sizeof(msg), fmt, va);
    pk_emerg("panic: %s", msg);

    for(;;) {
        /* WRONG WRONG WRONG! */
        asm volatile("cli");
        asm volatile("hlt");
    }
}

void __noreturn panic(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    panicv(fmt, va);
    va_end(va);
}
