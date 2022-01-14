/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <stivale2.h>
#include <sys/cdefs.h>
#include <sys/initcall.h>
#include <sys/intr.h>
#include <sys/klog.h>
#include <sys/kstring.h>
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
    klog(KLOG_INFO, "kernel version %s", CONFIG_VERSION);
    klog(KLOG_INFO, "bootloader: %s %s", st2.bootloader_brand, st2.bootloader_version);
    return 0;
}

initcall_early(version, init_version);
initcall_depn(version, klog);

void __used __noreturn xmain(const struct stivale2_struct *st)
{
    memcpy(&st2, st, sizeof(struct stivale2_struct));

    set_klog_level(KLOG_DEBUG);

    do_initcalls();

    enable_interrupts();
    for(;;) asm volatile("hlt");
}
