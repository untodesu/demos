/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <stivale2.h>
#include <sys/cdefs.h>
#include <sys/initcall.h>
#include <sys/interrupts.h>
#include <sys/printk.h>
#include <sys/string.h>
#include <x86/st2.h>

static void do_initcalls(void)
{
    size_t i;
    for(i = 0; initcalls[i]; i++) {
        /* ignore the return code for now */
        initcalls[i]();
    }
}

static int init_version(void)
{
    pk_info("kernel version %s", CONFIG_VERSION);
    pk_info("bootloader: %s %s", st2.bootloader_brand, st2.bootloader_version);
    return 0;
}

kernel_initcall(version, init_version);

void __used __noreturn xmain(const struct stivale2_struct *st)
{
    memcpy(&st2, st, sizeof(struct stivale2_struct));

    do_initcalls();

    enable_interrupts();
    for(;;) asm volatile("hlt");
}
