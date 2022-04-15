/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_PMEM_H_
#define _SYS_PMEM_H_ 1
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/initcall.h>
#include <sys/mmdefs.h>

void *pmalloc(size_t num_pages);
void *pmallocz(size_t num_pages);
void pmfree(void *page, size_t num_pages);

initcall_extern(pmem);

#endif
