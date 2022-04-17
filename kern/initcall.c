/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/initcall.h>

static void initcall_boot(void)
{

}

initcall(boot, initcall_boot);

static void initcall_setup(void)
{

}

initcall(setup, initcall_setup);
initcall_dependency(setup, boot);

static void initcall_kernel(void)
{

}

initcall(kernel, initcall_kernel);
initcall_dependency(kernel, setup);
