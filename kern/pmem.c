/* SPDX-License-Identifier: BSD-2-Clause */
#include <limine.h>
#include <sys/debug.h>
#include <sys/printk.h>
#include <sys/pmem.h>
#include <sys/string.h>

struct pmem_stats {
    size_t usable_memory;
    size_t used_memory;
    size_t used_pages;
};

typedef uint64_t pmem_page_t;

static uintptr_t phys_limit = 0;
static size_t total_pages = 0;
static struct pmem_stats stats = { 0 };
static uint32_t *bitmap = NULL;
static pmem_page_t alloc_temp = 0;

static volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0,
    .response = NULL
};

static volatile struct limine_memmap_request mmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
    .response = NULL
};

static inline int is_free(pmem_page_t begin, pmem_page_t end)
{
    pmem_page_t i;
    for(i = begin; i < end; i++) {
        if(bitmap[i / 32] & (1 << (i % 32)))
            continue;
        return 0;
    }

    return 1;
}

static inline int try_alloc(pmem_page_t begin, pmem_page_t end)
{
    pmem_page_t i;
    if(is_free(begin, end)) {
        for(i = begin; i < end; i++)
            bitmap[i / 32] &= ~(1 << (i % 32));
        stats.used_memory += (end - begin) * PAGE_SIZE;
        stats.used_pages += (end - begin);
        return 1;
    }

    return 0;
}

static inline pmem_page_t get_page(uintptr_t pptr)
{
    return __align_floor(pptr, PAGE_SIZE) / PAGE_SIZE;
}

void *pmalloc(size_t num_pages)
{
    pmem_page_t i;

    for(i = alloc_temp; i < total_pages; i++) {
        if(!try_alloc(i, i + num_pages))
            continue;
        alloc_temp = i;
        return pptr_to_vptr(i * PAGE_SIZE);
    }

    for(i = 0; i < alloc_temp; i++) {
        if(!try_alloc(i, i + num_pages))
            continue;
        alloc_temp = i;
        return pptr_to_vptr(i * PAGE_SIZE);
    }

    panic("pmem: out of memory");
    return NULL;
}

void *pmallocz(size_t num_pages)
{
    void *ptr = pmalloc(num_pages);
    if(ptr)
        memset(ptr, 0, num_pages * PAGE_SIZE);
    return ptr;
}

void pmfree(void *page, size_t num_pages)
{
    pmem_page_t i, begin, end;
    unsigned int pos, bit;

    begin = get_page(vptr_to_pptr(page));
    end = begin + num_pages;

    for(i = begin; i < end; i++) {
        pos = (i / 32);
        bit = (1 << (i % 32));
        if(bitmap[pos] & bit)
            continue;
        stats.used_memory -= PAGE_SIZE;
        stats.used_pages--;
        bitmap[pos] |= bit;
    }

    alloc_temp = begin;
}

uintptr_t vptr_to_pptr(void *vptr)
{
    return (uintptr_t)((uint64_t)vptr - hhdm_request.response->offset);
}

void *pptr_to_vptr(uintptr_t pptr)
{
    return (void *)((uint64_t)pptr + hhdm_request.response->offset);
}

static inline int check_address(uintptr_t paddr)
{
#if defined(__X86_64__)
    /* We don't like writing to low
     * memory areas, BIOS still might have
     * some valuable shit stored there. */
    return paddr >= 0x100000;
#else
    return 1;
#endif
}

static int init_pmem(void)
{
    uint64_t i;
    size_t bsz, kib_1, kib_2;
    uintptr_t new_phys_limit;
    pmem_page_t bitmap_page;
    const char *entry_type_str;
    const struct limine_memmap_entry *mmap_entry;

    kassert_msg(hhdm_request.response, "no hhdm info available");
    kassert_msg(mmap_request.response, "no memory map available");

    phys_limit = 0;
    stats.usable_memory = 0;
    total_pages = 0;

    for(i = 0; i < mmap_request.response->entry_count; i++) {
        mmap_entry = mmap_request.response->entries[i];
        switch(mmap_entry->type) {
            case LIMINE_MEMMAP_USABLE:
                entry_type_str = "usable";
                break;
            case LIMINE_MEMMAP_RESERVED:
                entry_type_str = "reserved";
                break;
            case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
                entry_type_str = "acpi reclaimable";
                break;
            case LIMINE_MEMMAP_ACPI_NVS:
                entry_type_str = "acpi nvs";
                break;
            case LIMINE_MEMMAP_BAD_MEMORY:
                entry_type_str = "bad memory";
                break;
            case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
                entry_type_str = "bootloader reclaimable";
                break;
            case LIMINE_MEMMAP_KERNEL_AND_MODULES:
                entry_type_str = "kernel and modules";
                break;
            case LIMINE_MEMMAP_FRAMEBUFFER:
                entry_type_str = "framebuffer";
                break;
            default:
                entry_type_str = "unknown";
                break;
        }

        new_phys_limit = mmap_entry->base + mmap_entry->length;

        if(mmap_entry->type != LIMINE_MEMMAP_RESERVED && mmap_entry->type != LIMINE_MEMMAP_KERNEL_AND_MODULES && new_phys_limit > phys_limit) {
            if(check_address((uintptr_t)(mmap_entry->base + mmap_entry->length))) {
                switch(mmap_entry->type) {
                    case LIMINE_MEMMAP_USABLE:
                    case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
                    case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
                        stats.usable_memory += mmap_entry->length;
                        break;
                }
            }
            phys_limit = new_phys_limit;
        }

        pk_debug("pmem: %p:%p - %s", (void *)mmap_entry->base, (void *)(new_phys_limit - 1), entry_type_str);
    }

    bitmap = NULL;
    total_pages = calc_num_pages(phys_limit);
    bsz = total_pages / 32 * sizeof(uint32_t);
    for(i = 0; i < mmap_request.response->entry_count; i++) {
        mmap_entry = mmap_request.response->entries[i];
        if(check_address((uintptr_t)(mmap_entry->base + mmap_entry->length))) {
            if(mmap_entry->type == LIMINE_MEMMAP_USABLE && mmap_entry->length >= bsz) {
                bitmap = pptr_to_vptr(mmap_entry->base);
                break;
            }
        }
    }

    memset(bitmap, 0, bsz);

    stats.used_pages = total_pages;
    stats.used_memory = stats.usable_memory;
    for(i = 0; i < mmap_request.response->entry_count; i++) {
        mmap_entry = mmap_request.response->entries[i];
        if(check_address((uintptr_t)(mmap_entry->base + mmap_entry->length))) {
            if(mmap_entry->type != LIMINE_MEMMAP_USABLE)
                continue;
            pmfree(pptr_to_vptr(mmap_entry->base), calc_num_pages(mmap_entry->length));
        }
    }

    bitmap_page = get_page(vptr_to_pptr(bitmap));
    kassert(try_alloc(bitmap_page, bitmap_page + calc_num_pages(bsz)));

    alloc_temp = 0;

    kib_1 = stats.used_memory / 1024;
    kib_2 = stats.usable_memory / 1024;
    pk_debug("pmem: bitmap: at=%p, size=%zu (%zu bytes)", (void *)bitmap, bsz / sizeof(uint32_t), bsz);
    pk_debug("pmem: %zu/%zu KiB (%zu/%zu MiB) used/usable", kib_1, kib_2, kib_1 / 1024, kib_2 / 1024);
    pk_debug("pmem: %zu/%zu pages used/total", stats.used_pages, total_pages);

    return 0;
}

setup_initcall(pmem, init_pmem);
