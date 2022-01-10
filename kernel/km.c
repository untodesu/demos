/* SPDX-License-Identifier: BSD-2-Clause */
#include <arch/pmm.h>
#include <sys/km.h>

struct km_info {
    size_t bytes;
    size_t pages;
};

void *kmalloc(size_t n)
{
    size_t np;
    unsigned char *ptr;
    struct km_info *info;

    /* Add an extra page for the metadata.
     * FIXME: this is a terrible way of doing this. 
     * such a small structure must not spend an entire
     * page. Something like a linked list of whatever 
     * would be much better. Possible TODO: kmalloc flags? */
    np = calc_num_pages(n) + 1;

    ptr = pmallocz(np);

    info = (void *)ptr;
    info->bytes = n;
    info->pages = np;

    return ptr + PAGE_SIZE;
}

void kmfree(void *s)
{
    if(s) {
        struct km_info *info = (void *)((char *)s - PAGE_SIZE);
        pmfree(info, info->pages);
    }
}
