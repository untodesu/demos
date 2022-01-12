/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/init.h>

static int init_early(void)
{
    return 0;
}

static int init_kernel(void)
{
    return 0;
}

declare_initcall(early, init_early);
declare_initcall(kernel, init_kernel);
initcall_dependency(kernel, early);
