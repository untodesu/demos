/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <stivale2.h>
#include <sys/cdefs.h>

static struct stivale2_tag __header_tag_0 = {
    .identifier = STIVALE2_HEADER_TAG_UNMAP_NULL_ID,
    .next = 0
};

__aligned(16) static uint8_t __boot_stack[CONFIG_BOOT_STACK_SIZE] = { 0 };
__section(".stivale2hdr") __used static struct stivale2_header __header = {
    .entry_point = 0,
    .stack = (uint64_t)(__boot_stack + sizeof(__boot_stack)),
    .flags = (1 << 1),
    .tags = (uint64_t)(&__header_tag_0)
};
