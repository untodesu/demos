/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/debug.h>
#include <sys/printk.h>
#include <sys/pmem.h>
#include <sys/string.h>

typedef uint64_t pmem_page_t;

static uintptr_t phys_limit = 0;
static size_t total_pages = 0;
static size_t used_pages = 0;
static uint32_t *bitmap = NULL;
static pmem_page_t alloc_temp = 0;

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
        used_pages += (end - begin);
        return 1;
    }

    return 0;
}

static inline pmem_page_t get_page(uintptr_t ptr)
{
    return __align_floor(ptr, PAGE_SIZE) / PAGE_SIZE;
}

void *pmalloc(size_t num_pages)
{
    pmem_page_t i;

    for(i = alloc_temp; i < total_pages; i++) {
        if(!try_alloc(i, i + num_pages))
            continue;
        alloc_temp = i;
        return phys_to_virt_data(i * PAGE_SIZE);
    }

    for(i = 0; i < alloc_temp; i++) {
        if(!try_alloc(i, i + num_pages))
            continue;
        alloc_temp = i;
        return phys_to_virt_data(i * PAGE_SIZE);
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

    begin = get_page(virt_to_phys_data(page));
    end = begin + num_pages;

    for(i = begin; i < end; i++) {
        pos = (i / 32);
        bit = (1 << (i % 32));
        if(bitmap[pos] & bit)
            continue;
        used_pages--;
        bitmap[pos] |= bit;
    }

    alloc_temp = begin;
}

static int init_pmem(void)
{
    uint64_t i;
    size_t bsz, num_tags;
    size_t free_kib, total_kib;
    uintptr_t new_phys_limit;
    pmem_page_t bitmap_page;
    struct pmem_tag_s tag;
    const char *tag_type;

    _pmem_setup_arch();

    num_tags = _pmem_get_num_tags();
    kassert_msg(num_tags, "pmem: no memory information provided");

    phys_limit = 0;
    total_pages = 0;
    total_kib = 0;
    used_pages = 0;

    for(i = 0; i < num_tags; i++) {
        kassert(_pmem_get_tag(i, &tag));

        switch(tag.type) {
            case PMEM_TYPE_RESV:
                tag_type = "resv";
                break;
            case PMEM_TYPE_MISC:
                tag_type = "misc";
                break;
            case PMEM_TYPE_KRNL:
                tag_type = "krnl";
                break;
            case PMEM_TYPE_FREE:
                tag_type = "free";
                break;
            default:
                tag_type = "some";
                break;
        }

        new_phys_limit = tag.base + tag.limit;

        if(tag.type != PMEM_TYPE_RESV && tag.type != PMEM_TYPE_KRNL && new_phys_limit > phys_limit) {
            total_kib += tag.limit;
            phys_limit = new_phys_limit;
        }

        pk_debug("pmem: %s tag %p:%p", tag_type, (void *)tag.base, (void *)(new_phys_limit - 1));
    }

    bitmap = NULL;
    total_pages = calc_num_pages(phys_limit);
    bsz = total_pages / 32 * sizeof(uint32_t);
    for(i = 0; i < num_tags; i++) {
        kassert(_pmem_get_tag(i, &tag));
        if(_pmem_addr_check(tag.base + tag.limit)) {
            if(tag.type == PMEM_TYPE_FREE && tag.limit >= bsz) {
                bitmap = phys_to_virt_data(tag.base);
                break;
            }
        }
    }

    memset(bitmap, 0, bsz);

    used_pages = total_pages;
    for(i = 0; i < num_tags; i++) {
        kassert(_pmem_get_tag(i, &tag));
        if(_pmem_addr_check(tag.base + tag.limit)) {
            if(tag.type != PMEM_TYPE_FREE)
                continue;
            pmfree(phys_to_virt_data(tag.base), calc_num_pages(tag.limit));
        }
    }

    bitmap_page = get_page(virt_to_phys_data(bitmap));
    kassert(try_alloc(bitmap_page, bitmap_page + calc_num_pages(bsz)));

    alloc_temp = 0;

    free_kib = (total_pages - used_pages) * PAGE_SIZE / 1024;
    total_kib /= 1024;
    pk_debug("pmem: bitmap: at=%p, size=%zu (%zu bytes)", (void *)bitmap, bsz / sizeof(uint32_t), bsz);
    pk_debug("pmem: %zu/%zu KiB (%zu/%zu MiB) free/usable", free_kib, total_kib, free_kib / 1024, total_kib / 1024);

    return 0;
}
setup_initcall(pmem, init_pmem);
