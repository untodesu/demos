/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/boot.h>
#include <sys/cpu.h>
#include <sys/debug.h>
#include <sys/initcall.h>
#include <sys/printk.h>
#include <sys/string.h>

struct stivale2_struct boot_struct = { 0 };

const void *find_boot_tag(uint64_t tag_identifier)
{
    const struct stivale2_tag *tag = (const void *)boot_struct.tags;
    while(tag) {
        if(tag->identifier == tag_identifier)
            return tag;
        tag = (const void *)tag->next;
    }

    return NULL;
}

static void do_initcalls(void)
{
    size_t i;
    for(i = 0; initcalls[i]; i++) {
        /* TODO: do not ignore
         * the return code. */
        initcalls[i]();
    }
}

void __noreturn boot_entry(const struct stivale2_struct *boot_struct_ptr)
{
    kassert_msg(boot_struct_ptr, "boot struct is null!");
    memcpy(&boot_struct, boot_struct_ptr, sizeof(struct stivale2_struct));

    pk_info("kernel version %s (rev %016lx)", CONFIG_VERSION, CONFIG_GIT_REV);
    pk_info("bootloader (%s) version %s", boot_struct.bootloader_brand, boot_struct.bootloader_version);

    do_initcalls();

    enable_interrupts();
    for(;;) {
        /* TODO: instead of straight up
         * halting the cpu here we maybe shall
         * chain-call an arch-specific code here.
         * Or, perhaps, we are fine since initcalls
         * do virtually all the work now... */
        cpu_halt();
    }
}

/* TODO: implement an initcall-alike system for
 * generating a list of boot tags on compile time
 * so we won't need to touch shit here ever again... */
static struct stivale2_tag boot_tag_0 = {
    .identifier = STIVALE2_HEADER_TAG_UNMAP_NULL_ID,
    .next = 0
};

__aligned(16) static uint8_t boot_stack[CONFIG_BOOT_STACK_SIZE] = { 0 };
__section(".stivale2hdr") __used static struct stivale2_header boot_header = {
    .entry_point = (uint64_t)(&boot_entry),
    .stack = (uint64_t)(boot_stack + sizeof(boot_stack)),
    .tags = (uint64_t)(&boot_tag_0),
    .flags = (1 << 1),
};
