/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_MMDEFS_H_
#define _SYS_MMDEFS_H_ 1

#define PAGE_SIZE 0x1000
#define PMEM_LOAD_BASE 0x0000000000200000
#define VMEM_CODE_BASE 0xFFFFFFFF80000000
#define VMEM_DATA_BASE4 0xFFFF800000000000
#define VMEM_DATA_BASE5 0xFF00000000000000

#ifndef __ASSEMBLER__
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

static inline void *phys_to_virt_code(uintptr_t ptr)
{
    /* code is always at a specific location */
    return (void *)(ptr + VMEM_CODE_BASE);
}

static inline void *phys_to_virt_data(uintptr_t ptr)
{
    /* data can be at different offsets depending on
     * paging level for a specific processor - TODO */
    return (void *)(ptr + VMEM_DATA_BASE4);
}

static inline uintptr_t virt_to_phys_code(const void *ptr)
{
   /* code is always at a specific location */
    return (uintptr_t)((unsigned char *)ptr - VMEM_CODE_BASE);
}

static inline uintptr_t virt_to_phys_data(const void *ptr)
{
    /* data can be at different offsets depending on
     * paging level for a specific processor - TODO */
    return (uintptr_t)((unsigned char *)ptr - VMEM_DATA_BASE4);
}

static inline size_t calc_num_pages(size_t num_bytes)
{
    return __align_ceil(num_bytes, PAGE_SIZE) / PAGE_SIZE;
}

#endif

#endif
