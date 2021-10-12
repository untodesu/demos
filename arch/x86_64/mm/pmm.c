#include <lib/string.h>
#include <mm/pmm.h>
#include <sys/klog.h>
#include <sys/panic.h>
#include <sys/stivale2.h>
#include <sys/vaddr.h>

#define PAGE_SIZE 4096

static const struct stivale2_struct_tag_memmap *mmap = NULL;
static struct pmm_info info = { 0 };
static uint8_t *bitmap = NULL;
static size_t pages_limit = 0;

static inline int is_free(uintptr_t begin, uintptr_t end)
{
    uintptr_t i;

    for(i = begin; i < end; i++) {
        if(bitmap[i / 8] & (1 << (i % 8)))
            continue;
        return 0;
    }

    return 1;
}

static inline int try_alloc(uintptr_t begin, uintptr_t end)
{
    uintptr_t i;

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
    return (n + PAGE_SIZE - 1) / PAGE_SIZE;
}

void init_pmm(const struct stivale2_struct_tag_memmap *tag)
{
    size_t bsz;
    uint64_t i;
    uintptr_t limit, bitmap_up;
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
            limit = ent->base + ent->length;
            if(limit > info.limit)
                info.limit = limit;
            info.total_memory += ent->length;
        }
    }

    pages_limit = calc_num_pages(info.limit);

    bitmap = NULL;
    bsz = info.limit / PAGE_SIZE / 8;

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

    bitmap_up = virt_to_phys((uintptr_t)bitmap);
    try_alloc(bitmap_up, bitmap_up + calc_num_pages(bsz));

    klog(KLOG_DEBUG, "pmm: bitmap: at=%p, size=%zu", (void *)bitmap, bsz);
    klog(KLOG_DEBUG, "pmm: memory: total=%zu KiB, used=%zu KiB", info.total_memory / 1024, info.used_memory / 1024);
    klog(KLOG_INFO, "pmm: init done");
}

/* UNDONE: we can't alloc yet */

void pmm_free(uintptr_t ptr, size_t num_pages)
{
    uintptr_t i, pos, bit;
    uintptr_t begin = ptr / PAGE_SIZE;
    uintptr_t end = begin + num_pages;
    size_t mem_size = num_pages * PAGE_SIZE;
    for(i = begin; i < end; i++) {
        pos = (i / 8);
        bit = (1 << (i % 8));
        if(!(bitmap[pos] & bit) && info.used_memory >= mem_size)
            info.used_memory -= mem_size;
        bitmap[pos] |= bit;
    }
}
