#include <drivers/i8253.h>
#include <drivers/i8259.h>
#include <drivers/st2t.h>
#include <lib/compiler.h>
#include <mm/pmm.h>
#include <sys/config.h>
#include <sys/exceptions.h>
#include <sys/interrupts.h>
#include <sys/klog.h>
#include <sys/segment.h>
#include <sys/stivale2.h>

static void __noreturn hang(void)
{
    /* UNDONE: move this somewhere else. */
    for(;;) asm volatile("hlt");
}

static const void *find_tag(const struct stivale2_struct *st, uint64_t identifier)
{
    const struct stivale2_tag *tag = (const void *)st->tags;
    while(tag) {
        if(tag->identifier == identifier)
            return tag;
        tag = (const void *)tag->next;
    }

    return NULL;
}

static void __noreturn init_arch(const struct stivale2_struct *st)
{
    disable_interrupts();

    init_klog();
    set_klog_level(KLOG_DEBUG);
    klog(KLOG_INFO, "version %s", VERSION);

    if(init_st2t(find_tag(st, STIVALE2_STRUCT_TAG_TERMINAL_ID))) {
        klog(KLOG_INFO, "klog: using st2t for early logging");
        set_klog_print_func(&st2t_write);
    }

    init_interrupts();
    init_exceptions();
    init_i8259();
    enable_interrupts();

    /* this panics */
    init_pmm(find_tag(st, STIVALE2_STRUCT_TAG_MEMMAP_ID));

    init_i8253();

    hang();
}

static struct stivale2_header_tag_terminal header_tag_1 = {
    .tag.identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
    .tag.next = 0,
    .flags = 0
};

static struct stivale2_header_tag_framebuffer header_tag_0 = {
    .tag.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
    .tag.next = (uint64_t)(&header_tag_1),
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};

__section(".bss") __aligned(16) static uint8_t boot_stack[X86_BOOT_STACK_SIZE] = { 0 };
__section(".stivale2hdr") __used static struct stivale2_header header = {
    .entry_point = (uint64_t)(&init_arch),
    .stack = (uint64_t)(boot_stack + sizeof(boot_stack)),
    .flags = (1 << 1) | (1 << 2),
    .tags = (uint64_t)(&header_tag_0)
};
