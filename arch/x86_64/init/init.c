#include <drivers/vgacon.h>
#include <lib/compiler.h>
#include <mm/pmm.h>
#include <sys/config.h>
#include <sys/i8253.h>
#include <sys/i8259.h>
#include <sys/interrupts.h>
#include <sys/klog.h>
#include <sys/panic.h>
#include <sys/stivale2.h>

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

void __used __noreturn kstart(const struct stivale2_struct *st2)
{
    disable_interrupts();

    init_klog();
    set_klog_level(KLOG_DEBUG);
    klog(KLOG_INFO, "kernel version: %s", VERSION);
    klog(KLOG_INFO, "bootloader: %s %s", st2->bootloader_brand, st2->bootloader_version);

    if(init_vgacon(find_st2_tag(st2, STIVALE2_STRUCT_TAG_TEXTMODE_ID)))
        set_klog_print_func(&vgacon_write);

    init_interrupts();
    init_i8259();    

    init_pmm(find_st2_tag(st2, STIVALE2_STRUCT_TAG_MEMMAP_ID));

    init_i8253();
    enable_interrupts();

    for(;;) asm volatile("hlt");
}

__section(".bss") __aligned(16) static uint8_t __boot_stack[X86_BOOT_STACK_SIZE] = { 0 };
__section(".stivale2hdr") __used static struct stivale2_header __boot_header = {
    .entry_point = (uint64_t)(&kstart),
    .stack = (uint64_t)(__boot_stack + sizeof(__boot_stack)),
    .flags = (1 << 1),
    .tags = 0
};
