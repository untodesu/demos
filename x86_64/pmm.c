/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/cdefs.h>
#include <sys/intr.h>
#include <sys/panic.h>
#include <sys/printk.h>
#include <sys/string.h>
#include <x86/pmm.h>
#include <x86/st2.h>
#include <stivale2.h>

typedef uint64_t pm_page_t;

static uintptr_t phys_limit = 0;
static size_t total_pages = 0;
static size_t used_pages = 0;
static uint32_t *bitmap = NULL;
static pm_page_t alloc_tmp = 0;

static inline int is_free(pm_page_t begin, pm_page_t end)
{
    pm_page_t i;

    for(i = begin; i < end; i++) {
        if(bitmap[i / 32] & (1 << (i % 32)))
            continue;
        return 0;
    }

    return 1;
}

static inline int try_alloc(pm_page_t begin, pm_page_t end)
{
    pm_page_t i;

    if(is_free(begin, end)) {
        for(i = begin; i < end; i++)
            bitmap[i / 32] &= ~(1 << (i % 32));
        used_pages += (end - begin);
        return 1;
    }

    return 0;
}

static inline pm_page_t get_page(uintptr_t addr)
{
    return __align_floor(addr, PAGE_SIZE) / PAGE_SIZE;
}

static inline int is_lma(uintptr_t addr)
{
    return addr <= 0x100000;
}

static int init_pmm(void)
{
    size_t bsz, free_kib, total_kib;
    uint64_t i;
    uintptr_t new_limit;
    pm_page_t bitmap_page;
    const struct stivale2_struct_tag_memmap *mmap;
    const struct stivale2_mmap_entry *entry;
    const char *entry_type_s;

    mmap = st2_find_tag(STIVALE2_STRUCT_TAG_MEMMAP_ID);
    if(!mmap) {
        /* FIXME: is this necessary considering most of
         * stivale-compliant bootloaders pass the mmap tag? */
        panic("pmm: no memmap was provided by the bootloader!");
        return 1;
    }

    phys_limit = 0;
    total_pages = 0;
    total_kib = 0;
    used_pages = 0;

    for(i = 0; i < mmap->entries; i++) {
        entry = mmap->memmap + i;

        switch(entry->type) {
            case STIVALE2_MMAP_USABLE:
                entry_type_s = "usable";
                break;
            case STIVALE2_MMAP_RESERVED:
                entry_type_s = "reserved";
                break;
            case STIVALE2_MMAP_ACPI_RECLAIMABLE:
                entry_type_s = "ACPI reclaim";
                break;
            case STIVALE2_MMAP_ACPI_NVS:
                entry_type_s = "ACPI NVS";
                break;
            case STIVALE2_MMAP_BAD_MEMORY:
                entry_type_s = "bad memory";
                break;
            case STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE:
                entry_type_s = "boot reclaim";
                break;
            case STIVALE2_MMAP_KERNEL_AND_MODULES:
                entry_type_s = "kernel";
                break;
            case STIVALE2_MMAP_FRAMEBUFFER:
                entry_type_s = "framebuffer";
                break;
            default:
                entry_type_s = "undefined";
                break;
        }

        new_limit = entry->base + entry->length;
    
        /* E820 data (either from the BIOS or from the bootloader)
         * tends to have RESERVED entries at the end of the table
         * that start at the true physical limit (say 128 MiB) and
         * end at 4 GiB or whatever value BIOS decides to use. */
        if(entry->type != STIVALE2_MMAP_RESERVED && entry->type != STIVALE2_MMAP_KERNEL_AND_MODULES && new_limit > phys_limit) {
            total_kib += entry->length;
            phys_limit = new_limit;
        }

        printk(LOGLEVEL_INFO, "pmm: mmap: [%p -> %p], %s", (void *)entry->base, (void *)(new_limit - 1), entry_type_s);
    }

    bitmap = NULL;
    total_pages = calc_num_pages(phys_limit);
    bsz = (total_pages / 32) * sizeof(uint32_t);
    for(i = 0; i < mmap->entries; i++) {
        entry = mmap->memmap + i;
        if(!is_lma(entry->base + entry->length)) {
            if(entry->type == STIVALE2_MMAP_USABLE && entry->length >= bsz) {
                bitmap = (uint32_t *)(entry->base + MEMORY_VIRTUAL_BASE);
                break;
            }
        }
    }

    memset(bitmap, 0, bsz);

    used_pages = total_pages;
    for(i = 0; i < mmap->entries; i++) {
        entry = mmap->memmap + i;
        if(!is_lma(entry->base + entry->length)) {
            if(entry->type != STIVALE2_MMAP_USABLE)
                continue;
            pmfree((void *)(entry->base + MEMORY_VIRTUAL_BASE), calc_num_pages(entry->length));
        }
    }

    bitmap_page = get_page((uintptr_t)bitmap - MEMORY_VIRTUAL_BASE);
    try_alloc(bitmap_page, bitmap_page + calc_num_pages(bsz));

    alloc_tmp = 0;

    free_kib = (total_pages - used_pages) * PAGE_SIZE / 1024;
    total_kib /= 1024;
    printk(LOGLEVEL_DEBUG, "pmm: bitmap: at=%p, size=%zu", (void *)bitmap, bsz / sizeof(uint32_t));
    printk(LOGLEVEL_DEBUG, "pmm: %zu/%zu KiB (%zu/%zu MiB) free/usable", free_kib, total_kib, free_kib / 1024, total_kib / 1024);

    return 0;
}

boot_initcall(pmm, init_pmm);
initcall_dependency(pmm, interrupts);

void *pmalloc(size_t num_pages)
{
    pm_page_t i;

    for(i = alloc_tmp; i < total_pages; i++) {
        if(!try_alloc(i, i + num_pages))
            continue;
        alloc_tmp = i;
        return (void *)((i * PAGE_SIZE) + MEMORY_VIRTUAL_BASE);
    }

    for(i = 0; i < alloc_tmp; i++) {
        if(!try_alloc(i, i + num_pages))
            continue;
        alloc_tmp = i;
        return (void *)((i * PAGE_SIZE) + MEMORY_VIRTUAL_BASE);
    }

    panic("pmm: out of memory!");
    return NULL;
}

void *pmallocz(size_t num_pages)
{
    void *ptr = pmalloc(num_pages);
    if(ptr)
        memset(ptr, 0, num_pages * PAGE_SIZE);
    return ptr;
}

void pmfree(void *ptr, size_t num_pages)
{
    pm_page_t i, begin, end;
    unsigned int pos, bit;

    begin = get_page((uintptr_t)ptr - MEMORY_VIRTUAL_BASE);
    end = begin + num_pages;

    for(i = begin; i < end; i++) {
        pos = (i / 32);
        bit = (1 << (i % 32));
        if(bitmap[pos] & bit)
            continue;
        used_pages--;
        bitmap[pos] |= bit;
    }

    /* Make sure we are able to re-use
     * the memory we just freed. */
    alloc_tmp = begin;
}
