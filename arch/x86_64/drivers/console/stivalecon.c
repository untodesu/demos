#include <drivers/console/stivalecon.h>
#include <sys/klog.h>
#include <sys/stivale2.h>

typedef void(*stivalecon_write_t)(const void *s, uint64_t n);
static stivalecon_write_t callback = NULL;

int init_stivalecon(const struct stivale2_struct_tag_terminal *tag)
{
    if(tag && tag->term_write) {
        callback = (stivalecon_write_t)tag->term_write;
        return 1;
    }

    return 0;
}

void stivalecon_write(const void *s, size_t n)
{
    if(!callback)
        return;
    callback(s, (uint64_t)n);
}
