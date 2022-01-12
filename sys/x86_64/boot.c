/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <stivale2.h>
#include <sys/cdefs.h>
#include <sys/cpu.h>
#include <sys/init.h>
#include <sys/interrupt.h>
#include <sys/klog.h>
#include <x86/i8253.h>
#include <x86/i8259.h>
#include <x86/pmm.h>
#include <x86/vm.h>

static const void *find_st2_tag(const struct stivale2_struct *st2, uint64_t identifier)
{
    const struct stivale2_tag *tag = (const void *)st2->tags;
    while(tag) {
        if(tag->identifier == identifier)
            return tag;
        tag = (const void *)tag->next;
    }

    return NULL;
}

static void __used __noreturn kmain(__unused struct stivale2_struct *st2)
{
    size_t i;
    for(i = 0; initcalls[i]; i++) {
        /* for now ignore the return code */
        initcalls[i]();
    }

    set_klog_level(KLOG_DBG);
    klog(KLOG_INF, "kernel version %s", CONFIG_VERSION);
    klog(KLOG_INF, "bootloader: %s %s", st2->bootloader_brand, st2->bootloader_version);

    init_pmm(find_st2_tag(st2, STIVALE2_STRUCT_TAG_MEMMAP_ID));

    init_i8259();
    init_i8253();

    cpu_enable_interrupts();
    for(;;) asm volatile("hlt");
}

static struct stivale2_tag __header_tag_0 = {
    .identifier = STIVALE2_HEADER_TAG_UNMAP_NULL_ID,
    .next = 0
};

__aligned(16) static uint8_t __boot_stack[CONFIG_BOOT_STACK_SIZE] = { 0 };
__section(".stivale2hdr") __used static struct stivale2_header __header = {
    .entry_point = (uint64_t)(&kmain),
    .stack = (uint64_t)(__boot_stack + sizeof(__boot_stack)),
    .flags = (1 << 1),
    .tags = (uint64_t)(&__header_tag_0)
};
