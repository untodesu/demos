#include <arch/i8253.h>
#include <arch/i8259.h>
#include <arch/interrupts.h>
#include <arch/mm.h>
#include <arch/segment.h>
#include <demos/compiler.h>
#include <demos/config.h>
#include <demos/klog.h>
#include <demos/kmalloc.h>
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

    if(init_tmvga(find_st2_tag(st2, STIVALE2_STRUCT_TAG_TEXTMODE_ID)))
        set_klog_print_func(&tmvga_write);

    init_interrupts();
    init_segment();

    init_pmm(find_st2_tag(st2, STIVALE2_STRUCT_TAG_MEMMAP_ID));

    void *test4096 = kmalloc(4096);
    klog(KLOG_DEBUG, "kmalloc(4096) = %p", test4096);

    void *test8192 = kmalloc(8192);
    klog(KLOG_DEBUG, "kmalloc(8192) = %p", test8192);

    kmfree(test8192);
    kmfree(test4096);

    void *test12288 = kmalloc(12288);
    klog(KLOG_DEBUG, "kmalloc(12288) = %p", test12288);

    kmfree(test12288);

    panic("nothing to do!");
}
