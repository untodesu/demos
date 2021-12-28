#include <config.h>
#include <arch/i8253.h>
#include <arch/i8259.h>
#include <arch/intr.h>
#include <arch/pmm.h>
#include <arch/seg.h>
#include <demos/compiler.h>
#include <demos/klog.h>
#include <demos/km.h>
#include <demos/panic.h>
#include <stivale2.h>

#include "tmvga.h"

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

void __used __noreturn stmain(__unused struct stivale2_struct *st2)
{
    init_klog();
    set_klog_level(KLOG_DEBUG);
    klog(KLOG_INFO, "kernel version %s", VERSION);
    klog(KLOG_INFO, "bootloader: %s %s", st2->bootloader_brand, st2->bootloader_version);

    setup_gdt();
    init_interrupts();

    init_pmm(find_st2_tag(st2, STIVALE2_STRUCT_TAG_MEMMAP_ID));

    if(init_tmvga(find_st2_tag(st2, STIVALE2_STRUCT_TAG_TEXTMODE_ID)))
        set_klog_print_func(&tmvga_write);

    init_i8259();
    init_i8253();

    cpu_enable_interrupts();
    for(;;) asm volatile("hlt");
}
