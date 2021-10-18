#include <arch/mm.h>
#include <demos/kmalloc.h>

/* FIXME: this little structure takes
 * AN ENTIRE PAGE to store itself. This is
 * unacceptable. Something like a linked list
 * of these guys would be much better... */
struct km_metadata {
    size_t num_pages;
};

void *kmalloc(size_t n)
{
    size_t num_pages = calc_num_pages(n) + 1;
    char *ptr = pmm_allocz(num_pages);
    struct km_metadata *metadata = (void *)ptr;
    metadata->num_pages = num_pages;
    return ptr + PAGE_SIZE;
}

void kmfree(void *s)
{
    struct km_metadata *metadata = (void *)((char *)s - PAGE_SIZE);
    pmm_free(metadata, metadata->num_pages);
}
