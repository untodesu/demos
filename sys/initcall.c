/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 23:13:05 */
#include <sys/initcall.h>

static int init_tier_0(void)
{
    return 0;
}
initcall(tier_0, init_tier_0);
initcall_dependency(tier_1, tier_0);

static int init_tier_1(void)
{
    return 0;
}
initcall(tier_1, init_tier_1);
initcall_dependency(tier_2, tier_1);

static int init_tier_2(void)
{
    return 0;
}
initcall(tier_2, init_tier_2);
initcall_dependency(tier_3, tier_2);

static int init_tier_3(void)
{
    return 0;
}
initcall(tier_3, init_tier_3);
