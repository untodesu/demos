#include <arch/stivale2.h>
#include <config.h>
#include <demos/cdefs.h>

/* arch/x86/init/init.c */
void __noreturn init_arch(void);

static void  __noreturn start(struct stivale2_struct *stivale)
{
    (void)(stivale);
    init_arch();
}

__section(".bss") static uint8_t stack[CONFIG_X86_BOOT_STACK_SIZE];
__section(".stivale2hdr") __used static struct stivale2_header header = {
    .entry_point = (uint64_t)(&start),
    .stack = (uint64_t)(stack + sizeof(stack)),
    .flags = (1 << 0),
    .tags = 0
};
