#include <lib/align.h>
#include <lib/string.h>
#include <mm/pmm.h>
#include <sys/klog.h>
#include <sys/panic.h>
#include <sys/stivale2.h>
#include <sys/vaddr.h>

#define PAGE_SIZE 4096

typedef uint64_t pmm_page_t;

static const struct stivale2_struct_tag_memmap *mmap = NULL;
static struct pmm_info info = { 0 };
static uint8_t *bitmap = NULL;
static size_t pages_limit = 0;

static inline int is_free(pmm_page_t begin, pmm_page_t end)
{
    pmm_page_t i;

    for(i = begin; i < end; i++) {
        if(bitmap[i / 8] & (1 << (i % 8)))
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
            bitmap[i / 8] &= ~(1 << (i % 8));
        info.used_memory += (end - begin) * PAGE_SIZE;
        return 1;
    }

    return 0;
}

static inline size_t calc_num_pages(size_t n)
{
    return ALIGN_CEIL(n, PAGE_SIZE) / PAGE_SIZE;
}

static inline pmm_page_t get_page_id(uintptr_t addr)
{
    return ALIGN_FLOOR(addr, PAGE_SIZE) / PAGE_SIZE;
}

void init_pmm(const struct stivale2_struct_tag_memmap *tag)
{
    size_t bsz;
    uint64_t i;
    uintptr_t new_limit;
    pmm_page_t bitmap_page;
    const struct stivale2_mmap_entry *ent;

    if(!(mmap = tag)) {
        /* FIXME: is this necessary considering most of
         * stivale-compliant bootloaders pass the mmap tag? */
        panic("pmm: no memory map was provided by the bootloader");
    }

    info.limit = 0;
    info.total_memory = 0;
    info.used_memory = 0;

    for(i = 0; i < mmap->entries; i++) {
        ent = mmap->memmap + i;
        if(ent->type == STIVALE2_MMAP_USABLE || ent->type == STIVALE2_MMAP_ACPI_RECLAIMABLE || ent->type == STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE || ent->type == STIVALE2_MMAP_KERNEL_AND_MODULES) {
            new_limit = ent->base + ent->length;
            if(new_limit > info.limit)
                info.limit = new_limit;
            info.total_memory += ent->length;
        }
    }

    pages_limit = calc_num_pages((size_t)info.limit);

    bitmap = NULL;
    bsz = pages_limit / 8;

    for(i = 0; i < mmap->entries; i++) {
        ent = mmap->memmap + i;
        if(ent->type == STIVALE2_MMAP_USABLE && ent->length >= bsz) {
            bitmap = (uint8_t *)phys_to_virt(ent->base);
            break;
        }
    }

    memset(bitmap, 0, bsz);

    info.used_memory = info.total_memory;
    for(i = 0; i < mmap->entries; i++) {
        ent = mmap->memmap + i;
        if(ent->type != STIVALE2_MMAP_USABLE)
            continue;
        pmm_free(ent->base, calc_num_pages(ent->length));
    }

    bitmap_page = get_page_id(virt_to_phys((uintptr_t)bitmap));
    try_alloc(bitmap_page, bitmap_page + calc_num_pages(bsz));

    klog(KLOG_DEBUG, "pmm: bitmap: at=%p, size=%zu", (void *)bitmap, bsz);
    klog(KLOG_DEBUG, "pmm: memory: total=%zu KiB, used=%zu KiB", info.total_memory / 1024, info.used_memory / 1024);
}

/* UNDONE: we can't alloc yet */

void pmm_free(uintptr_t addr, size_t num_pages)
{
    pmm_page_t i, begin, end;
    unsigned int pos, bit;

    begin = get_page_id(addr);
    end = begin + num_pages;

    for(i = begin; i < end; i++) {
        pos = (i / 8);
        bit = (1 << (i % 8));
        if(!(bitmap[pos] & bit))
            info.used_memory -= PAGE_SIZE;
        bitmap[pos] |= bit;
    }
}
