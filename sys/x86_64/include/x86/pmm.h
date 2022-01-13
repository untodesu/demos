/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _X86_PMM_H_
#define _X86_PMM_H_ 1
#include <sys/cdefs.h>
#include <sys/initcall.h>
#include <x86/vaddr.h>
#include <stddef.h>

void *pmalloc(size_t num_pages);
void *pmallocz(size_t num_pages);
void pmfree(void *ptr, size_t num_pages);

static inline size_t calc_num_pages(size_t num_bytes)
{
    return __align_ceil(num_bytes, PAGE_SIZE) / PAGE_SIZE;
}

initcall_extr(pmm);

#endif
