/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/initcall.h>

static int early_initcall(void)
{
    /* stub */
    return 0;
}

static int kernel_initcall(void)
{
    /* stub */
    return 0;
}

initcall_link(early, early_initcall);
initcall_link(kernel, kernel_initcall);
