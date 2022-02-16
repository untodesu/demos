/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/debug.h>
#include <sys/pmem.h>
#include <sys/string.h>
#include <x86/st2.h>

static const struct stivale2_struct_tag_memmap *mmap_tag = { 0 };

void _pmem_setup_arch(void)
{
    mmap_tag = st2_find_tag(STIVALE2_STRUCT_TAG_MEMMAP_ID);
    kassert_msg(mmap_tag, "pmem: no memory info was provided by the bootloader");
}

size_t _pmem_get_num_tags(void)
{
    return mmap_tag->entries;
}

int _pmem_get_tag(size_t id, struct pmem_tag_s *tag)
{
    if(!tag || id >= mmap_tag->entries)
        return 0;
    tag->base = mmap_tag->memmap[id].base;
    tag->limit = mmap_tag->memmap[id].length;
    switch(mmap_tag->memmap[id].type) {
        case STIVALE2_MMAP_RESERVED:
            tag->type = PMEM_TYPE_RESV;
            break;
        case STIVALE2_MMAP_KERNEL_AND_MODULES:
            tag->type = PMEM_TYPE_KRNL;
            break;
        case STIVALE2_MMAP_USABLE:
            tag->type = PMEM_TYPE_FREE;
            break;
        default:
            tag->type = PMEM_TYPE_MISC;
            break;
    }
    return 1;
}

int _pmem_addr_check(uintptr_t ptr)
{
    return ptr >= 0x100000;
}
