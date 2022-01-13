/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/init.h>

static int early_init(void)
{
    /* this is a stub initcall
     * required to just be here */
    return 0;
}

initcall_link(early, early_init);
