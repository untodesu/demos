/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sun Apr 24 2022 00:14:12 */
#include <ksprintf.h>
#include <sys/cpu.h>
#include <sys/intr.h>
#include <sys/debug.h>
#include <sys/kp.h>

void __noreturn panicv(const char *fmt, va_list va)
{
    static char msg[1024] = { 0 };
    kvsnprintf(msg, sizeof(msg), fmt, va);
    kp_emerg("kernel panic - %s", msg);
    disable_intrs();
    for(;;)
        halt_cpu();
}

void __noreturn panic(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    panicv(fmt, va);
    va_end(va);
}
