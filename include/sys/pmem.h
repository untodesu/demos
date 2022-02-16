/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_PMEM_H_
#define _SYS_PMEM_H_ 1
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/initcall.h>
#include <sys/mmdefs.h>

#define PMEM_TYPE_RESV 0 /* reserved                    */
#define PMEM_TYPE_MISC 1 /* free, but not free...       */
#define PMEM_TYPE_KRNL 2 /* kernel with modules         */
#define PMEM_TYPE_FREE 3 /* free for use                */

struct pmem_tag_s {
    unsigned short type;
    uintptr_t base;
    size_t limit;
};

void _pmem_setup_arch(void);
size_t _pmem_get_num_tags(void);
int _pmem_get_tag(size_t id, struct pmem_tag_s *tag);
int _pmem_addr_check(uintptr_t ptr);

void *pmalloc(size_t num_pages);
void *pmallocz(size_t num_pages);
void pmfree(void *page, size_t num_pages);

initcall_extern(pmem);

#endif
