/* SPDX-License-Identifier: BSD-2-Clause */
#include <x86/st2.h>

struct stivale2_struct st2 = { 0 };

const void *st2_find_tag(uint64_t identifier)
{
    const struct stivale2_tag *tag = (const void *)st2.tags;
    while(tag) {
        if(tag->identifier == identifier)
            return tag;
        tag = (const void *)tag->next;
    }

    return NULL;
}
