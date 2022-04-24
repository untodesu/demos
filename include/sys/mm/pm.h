/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:21:25 */
#ifndef _SYS_MM_PM_H_
#define _SYS_MM_PM_H_ 1
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/initcall.h>

#if !defined(PAGE_SIZE)
#define PAGE_SIZE 4096
#endif

struct pminfo_s {
    size_t free;
    size_t usable;
};

static inline size_t get_num_pages(size_t n)
{
    return __align_ceil(n, PAGE_SIZE) / PAGE_SIZE;
}

void *pmalloc(void);
void *pmalloc_r(size_t n);
void pmfree(void *vaddr);
void pmfree_r(void *vaddr, size_t n);

typedef uintptr_t paddr_t;
uintptr_t get_poffset(void);
paddr_t get_paddr(void *vaddr);
void *get_vaddr(paddr_t paddr);
void get_pminfo(struct pminfo_s *p);

initcall_extern(pm);

#endif
