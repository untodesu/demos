/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/initcall.h>

static int initcall_boot(void)
{
    return 0;
}

initcall(boot, initcall_boot);

static int initcall_setup(void)
{
    return 0;
}

initcall(setup, initcall_setup);
initcall_dependency(setup, boot);

static int initcall_kernel(void)
{
    return 0;
}

initcall(kernel, initcall_kernel);
initcall_dependency(kernel, setup);
