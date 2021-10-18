#ifndef _ARCH_MM_H_
#define _ARCH_MM_H_ 1

#define MEMORY_VIRTUAL_BASE 0xFFFF800000000000
#define KERNEL_VIRTUAL_BASE 0xFFFFFFFF80000000
#define KERNEL_LOAD_ADDRESS 0x0000000000200000
#define PAGE_SIZE           0x1000

#if !defined(__ASSEMBLER__)
#include <align.h>
#include <stddef.h>

struct stivale2_struct_tag_memmap;

void init_pmm(const struct stivale2_struct_tag_memmap *mmap);
void *pmm_alloc(size_t num_pages);
void *pmm_allocz(size_t num_pages);
void pmm_free(void *ptr, size_t num_pages);

static inline size_t calc_num_pages(size_t num_bytes)
{
    return ALIGN_CEIL(num_bytes, PAGE_SIZE) / PAGE_SIZE;
}
#endif

#endif
