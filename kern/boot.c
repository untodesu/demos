/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <limine.h>
#include <sys/debug.h>
#include <sys/initcall.h>
#include <sys/intr.h>
#include <sys/printk.h>
#include <sys/string.h>

static void kmain(void) __noreturn;
static volatile struct limine_entry_point_request __used kmain_request = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .revision = 0,
    .response = NULL,
    .entry = (limine_entry_point)(&kmain)
};

static volatile struct limine_bootloader_info_request __used bootloader_info = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0,
    .response = NULL
};

static void do_initcalls(void)
{
    size_t i;
    for(i = 0; initcalls[i]; i++) {
        if(!initcalls[i])
            continue;
        initcalls[i]();
    }
}

static void __noreturn kmain(void)
{
    const char *bootloader_name = "Limine-compliant";
    const char *bootloader_version = "unknown";
    if(bootloader_info.response) {
        bootloader_name = bootloader_info.response->name;
        bootloader_version = bootloader_info.response->version;
    }

    pk_info("kernel version %s (rev %016lx)", CONFIG_VERSION, CONFIG_GIT_REV);
    pk_info("bootloader (%s) version %s", bootloader_name, bootloader_version);

    do_initcalls();

    enable_intrs();
    for(;;) {
        /* Should we wait here? Should our
         * code even get here in future? */
        wait_for_intrs();
    }
}
