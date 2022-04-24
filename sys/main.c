/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sun Apr 24 2022 13:58:09 */
#include <limine.h>
#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/debug.h>
#include <sys/initcall.h>
#include <sys/mm/pm.h>
#include <sys/kp.h>

static void kmain(void) __noreturn;
static volatile struct limine_entry_point_request __used entrypoint = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .revision = 0,
    .response = NULL,
    .entry = (limine_entry_point)&kmain
};

static void __noreturn kmain(void)
{
    size_t i;
    for(i = 0; initcalls[i]; i++) {
        /* TODO: check the return code. */
        initcalls[i]();
    }

    /* Test pmalloc (per-page allocation) */
    void *pmt1, *pmt2, *pmt3;
    kp_inform("PMALLOC TEST:");
    kp_inform(" alloc page: %p", pmt1 = pmalloc());
    kp_inform(" alloc page: %p", pmt2 = pmalloc());
    kp_inform(" alloc page: %p", pmt3 = pmalloc());
    pmfree(pmt3);
    pmfree(pmt2);
    pmfree(pmt1);

    /* Test pmalloc_r (page range allocation) */
    void *pmrt1, *pmrt2, *pmrt3;
    kp_inform("PMALLOC_R TEST:");
    kp_inform(" alloc 3 pages:  %p", pmrt1 = pmalloc_r(3));
    kp_inform(" alloc 7 pages:  %p", pmrt2 = pmalloc_r(7));
    kp_inform(" free previous allocations");
    pmfree_r(pmrt2, 7); pmfree_r(pmrt1, 3);
    kp_inform(" alloc 10 pages: %p", pmrt3 = pmalloc_r(10));
    pmfree_r(pmrt3, 10);
    kp_inform(" pmalloc alloc:  %p", pmrt1 = pmalloc());
    pmfree(pmrt1);

    panic("nothing to do");
}

