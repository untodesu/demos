/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_PMEM_H_
#define _SYS_PMEM_H_ 1
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/initcall.h>

#if !defined(PAGE_SIZE)
/* I am not editing VSCode config again */
#define PAGE_SIZE 4096
#endif

void *pmalloc(size_t num_pages);
void *pmallocz(size_t num_pages);
void pmfree(void *page, size_t num_pages);

/* These now require a HHDM feature */
uintptr_t vptr_to_pptr(void *vptr);
void *pptr_to_vptr(uintptr_t pptr);

static inline size_t calc_num_pages(size_t num_bytes)
{
    return __align_ceil(num_bytes, PAGE_SIZE) / PAGE_SIZE;
}

initcall_extern(pmem);

#endif
