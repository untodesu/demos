/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:21:12 */
#include <limine.h>
#include <string.h>
#include <sys/debug.h>
#include <sys/kp.h>
#include <sys/mm/pm.h>

typedef uintptr_t page_t;

static paddr_t phys_limit = 0;
static paddr_t phys_offset = 0;
static size_t num_pages = 0;
static size_t free_pages = 0;
static size_t usable_pages = 0;
static uint32_t *bitmap = NULL;
static page_t last_page = 0;

static volatile struct limine_hhdm_request hhdm = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0,
    .response = NULL
};

static volatile struct limine_memmap_request memmap = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
    .response = NULL
};

static int check_bit(size_t off, uint32_t bit)
{
    return bitmap[off] & bit;
}

static int occupy_page(page_t p)
{
    size_t off = (size_t)(p / 32);
    uint32_t bit = (uint32_t)(1 << (p % 32));
    if(check_bit(off, bit)) {
        bitmap[off] &= ~bit;
        return 1;
    }

    return 0;
}

static int occupy_range(page_t p1, page_t p2)
{
    page_t i;
    size_t off;
    uint32_t bit;
    for(i = p1; i <= p2; i++) {
        off = (size_t)(i / 32);
        bit = (uint32_t)(1 << (i % 32));
        if(!check_bit(off, bit))
            goto alloc_failed;
        bitmap[off] &= ~bit;
    }

    return 1;

alloc_failed:
    while(i >= p1) {
        off = (size_t)(i / 32);
        bit = (uint32_t)(1 << (i % 32));
        bitmap[off] |= bit;
        i--;
    }

    return 0;
}

static page_t get_page(paddr_t p)
{
    return __align_floor(p, PAGE_SIZE) / PAGE_SIZE;
}

void *pmalloc(void)
{
    page_t i;

    /* Try to continue allocating through. */
    for(i = last_page; i < num_pages; i++) {
        if(!occupy_page(i))
            continue;
        last_page = i + 1;
        free_pages--;
        return get_vaddr(i * PAGE_SIZE);
    }

    /* Try to allocate from the begining. */
    for(i = 0; i < last_page; i++) {
        if(!occupy_page(i))
            continue;
        last_page = i + 1;
        free_pages--;
        return get_vaddr(i * PAGE_SIZE);
    }

    /* Give up */
    panic("pm: out of physical memory");
    return NULL;
}

void *pmalloc_r(size_t n)
{
    page_t i;

    /* Try to continue allocating through. */
    for(i = last_page; i < num_pages; i++) {
        if(!occupy_range(i, i + n - 1))
            continue;
        last_page = i + 1;
        free_pages -= n;
        return get_vaddr(i * PAGE_SIZE);
    }

    /* Try to allocate from the begining. */
    for(i = 0; i < last_page; i++) {
        if(!occupy_range(i, i + n - 1))
            continue;
        last_page = i + 1;
        free_pages -= n;
        return get_vaddr(i * PAGE_SIZE);
    }

    /* Give up */
    panic("pm: out of physical memory");
    return NULL;
}

void pmfree(void *vaddr)
{
    page_t p = get_page(get_paddr(vaddr));
    size_t off = (size_t)(p / 32);
    uint32_t bit = (uint32_t)(1 << (p % 32));
    bitmap[off] |= bit;
    last_page = p;
    free_pages++;
}

void pmfree_r(void *vaddr, size_t n)
{
    size_t off;
    uint32_t bit;
    page_t i, p1, p2;

    p1 = get_page(get_paddr(vaddr));
    p2 = p1 + n - 1;

    for(i = p1; i <= p2; i++) {
        off = (size_t)(i / 32);
        bit = (uint32_t)(1 << (i % 32));
        bitmap[off] |= bit;
    }

    last_page = p1;
    free_pages += n;
}

uintptr_t get_poffset(void)
{
    return phys_offset;
}

paddr_t get_paddr(void *vaddr)
{
    return (paddr_t)((uintptr_t)vaddr - phys_offset);
}

void *get_vaddr(paddr_t paddr)
{
    return (void *)((uintptr_t)paddr + phys_offset);
}

void get_pminfo(struct pminfo_s *p)
{
    p->free = free_pages;
    p->usable = usable_pages;
}

static int init_pm(void)
{
    uint64_t i;
    size_t bsize;
    page_t bpage;
    uintptr_t new_phys_limit;
    const struct limine_memmap_entry *entry;
    const char *entry_str;
    size_t sz_1, sz_2;

    panic_unless_msg(hhdm.response, "pm: no boot response for hhdm request");
    panic_unless_msg(memmap.response, "pm: no boot response for memmap request");

    phys_limit = 0;
    phys_offset = hhdm.response->offset;
    free_pages = 0;
    usable_pages = 0;

    /* Get the physical memory limit. */
    for(i = 0; i < memmap.response->entry_count; i++) {
        entry = memmap.response->entries[i];
        switch(entry->type) {
            case LIMINE_MEMMAP_USABLE:
                entry_str = "usable";
                break;
            case LIMINE_MEMMAP_RESERVED:
                entry_str = "reserved";
                break;
            case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
                entry_str = "acpi reclaimable";
                break;
            case LIMINE_MEMMAP_ACPI_NVS:
                entry_str = "acpi nvs";
                break;
            case LIMINE_MEMMAP_BAD_MEMORY:
                entry_str = "bad memory";
                break;
            case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
                entry_str = "bootloader reclaimable";
                break;
            case LIMINE_MEMMAP_KERNEL_AND_MODULES:
                entry_str = "kernel and modules";
                break;
            case LIMINE_MEMMAP_FRAMEBUFFER:
                entry_str = "framebuffer";
                break;
            default:
                entry_str = "unknown";
                break;
        }

        new_phys_limit = entry->base + entry->length;
        do {
            if(entry->type == LIMINE_MEMMAP_RESERVED)
                break;
            if(entry->type == LIMINE_MEMMAP_KERNEL_AND_MODULES)
                break;
            if(new_phys_limit <= phys_limit)
                break;
            phys_limit = new_phys_limit;
        } while(0);

        switch(entry->type) {
            case LIMINE_MEMMAP_USABLE:
            case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
            case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
                usable_pages += get_num_pages(entry->length);
                break;
        }

        kp_debug("pm: %p:%p - %s", (const void *)entry->base, (const void *)(new_phys_limit - 1), entry_str);
    }

    bitmap = NULL;


    num_pages = get_num_pages(phys_limit);
    bsize = num_pages / 32;

    /* Allocate the bitmap */
    for(i = 0; i < memmap.response->entry_count; i++) {
        entry = memmap.response->entries[i];
        if(entry->type == LIMINE_MEMMAP_USABLE && entry->length >= bsize) {
            bitmap = get_vaddr(entry->base);
            break;
        }
    }

    panic_unless_msg(bitmap, "pm: not enough physical memory");

    /* Mark the usable space as FREE */
    for(i = 0; i < memmap.response->entry_count; i++) {
        entry = memmap.response->entries[i];
        if(entry->type != LIMINE_MEMMAP_USABLE)
            continue;
        pmfree_r(get_vaddr(entry->base), get_num_pages(entry->length));
    }

    /* Mark the bitmap by itself as USED */
    sz_1 = get_num_pages(bsize);
    bpage = get_page(get_paddr(bitmap));
    occupy_range(bpage, bpage + sz_1 - 1);
    free_pages -= sz_1;

    /* Force the allocator to start searching
     * at the first available page instead of
     * the last one occupied */
    last_page = 0;
    pmfree(pmalloc());

    sz_1 = free_pages * PAGE_SIZE / 1024;
    sz_2 = usable_pages * PAGE_SIZE / 1024;
    kp_inform("pm: phys_limit=%p, num_pages=%zu", (void *)phys_limit, num_pages);
    kp_inform("pm: %zu/%zu KiB free/usable (%zu KiB used)", sz_1, sz_2, sz_2 - sz_1);

    return 0;
}
initcall_tier_1(pm, init_pm);
