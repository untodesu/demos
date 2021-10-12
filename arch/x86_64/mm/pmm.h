#ifndef __MM_PMM_H__
#define __MM_PMM_H__ 1
#include <lib/inttypes.h>
#include <lib/stddef.h>

struct stivale2_struct_tag_memmap;

struct pmm_info {
    uintptr_t limit;
    size_t total_memory;
    size_t used_memory;
};

void init_pmm(const struct stivale2_struct_tag_memmap *tag);
void pmm_free(uintptr_t ptr, size_t num_pages);

#endif
