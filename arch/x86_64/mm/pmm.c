#include <arch/mm.h>
#include <demos/compiler.h>
#include <demos/klog.h>
#include <demos/panic.h>
#include <stivale2.h>
#include <string.h>

typedef uint64_t pmm_page_t;

static uintptr_t phys_limit = 0;
static size_t total_pages = 0;
static size_t used_pages = 0;
static uint32_t *bitmap = NULL;
static pmm_page_t alloc_tmp = 0;

static inline int is_free(pmm_page_t begin, pmm_page_t end)
{
    pmm_page_t i;

    for(i = begin; i < end; i++) {
        if(bitmap[i / 32] & (1 << (i % 32)))
            continue;
        return 0;
    }

    return 1;
}

static inline int try_alloc(pmm_page_t begin, pmm_page_t end)
{
    pmm_page_t i;

    if(is_free(begin, end)) {
        for(i = begin; i < end; i++)
            bitmap[i / 32] &= ~(1 << (i % 32));
        used_pages += (end - begin);
        return 1;
    }

    return 0;
}

static inline pmm_page_t get_page(uintptr_t addr)
{
    return ALIGN_FLOOR(addr, PAGE_SIZE) / PAGE_SIZE;
}

static inline int is_lma(uintptr_t addr)
{
    return addr <= 0x100000;
}

void init_pmm(const struct stivale2_struct_tag_memmap *mmap)
{
    size_t bsz, total_kib;
    uint64_t i;
    uintptr_t new_limit;
    pmm_page_t bitmap_page;
    const struct stivale2_mmap_entry *entry;

    if(!mmap) {
        /* FIXME: is this necessary considering most of
         * stivale-compliant bootloaders pass the mmap tag? */
        panic("pmm: no memmap was provided by the bootloader!");
    }

    phys_limit = 0;
    total_pages = 0;
    used_pages = 0;

    for(i = 0; i < mmap->entries; i++) {
        entry = mmap->memmap + i;

        new_limit = entry->base + entry->length;
        if(is_lma(new_limit))
            continue;

        if(new_limit > phys_limit)
            phys_limit = new_limit;

        if(entry->type == STIVALE2_MMAP_USABLE || entry->type == STIVALE2_MMAP_ACPI_RECLAIMABLE || entry->type == STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE || entry->type == STIVALE2_MMAP_KERNEL_AND_MODULES)
            total_pages += calc_num_pages(entry->length);
    }

    bitmap = NULL;
    bsz = (total_pages / 32) * sizeof(uint32_t);
    for(i = 0; i < mmap->entries; i++) {
        entry = mmap->memmap + i;

        new_limit = entry->base + entry->length;
        if(is_lma(new_limit))
            continue;

        if(entry->type == STIVALE2_MMAP_USABLE && entry->length >= bsz) {
            bitmap = (uint32_t *)(entry->base + MEMORY_VIRTUAL_BASE);
            break;
        }
    }

    memset(bitmap, 0, bsz);

    used_pages = total_pages;
    for(i = 0; i < mmap->entries; i++) {
        entry = mmap->memmap + i;

        new_limit = entry->base + entry->length;
        if(is_lma(new_limit))
            continue;

        if(entry->type != STIVALE2_MMAP_USABLE)
            continue;
        pmm_free((void *)(entry->base + MEMORY_VIRTUAL_BASE), calc_num_pages(entry->length));
    }

    bitmap_page = get_page((uintptr_t)bitmap - MEMORY_VIRTUAL_BASE);
    try_alloc(bitmap_page, bitmap_page + calc_num_pages(bsz));

    alloc_tmp = 0;

    total_kib = (total_pages * PAGE_SIZE) / 1024;
    klog(KLOG_DEBUG, "pmm: bitmap: at=%p, size=%zu", (void *)bitmap, bsz);
    klog(KLOG_DEBUG, "pmm: total memory: %zu KiB (%zu MiB)", total_kib, total_kib / 1024);
}

void *pmm_alloc(size_t num_pages)
{
    pmm_page_t i;

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

void *pmm_allocz(size_t num_pages)
{
    void *ptr = pmm_alloc(num_pages);
    if(ptr)
        memset(ptr, 0, num_pages * PAGE_SIZE);
    return ptr;
}

void pmm_free(void *ptr, size_t num_pages)
{
    pmm_page_t i, begin, end;
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
