#include <demos/compiler.h>
#include <demos/config.h>
#include <stivale2.h>

__aligned(16) static uint8_t __boot_stack[X86_BOOT_STACK_SIZE] = { 0 };
__section(".stivale2hdr") __used static struct stivale2_header __header = {
    .entry_point = 0,
    .stack = (uint64_t)(__boot_stack + sizeof(__boot_stack)),
    .flags = (1 << 1),
    .tags = 0
};