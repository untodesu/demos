#include <drivers/st2t.h>
#include <sys/stivale2.h>

typedef void(*st2t_write_t)(const void *s, uint64_t n);
static st2t_write_t callback = NULL;

int init_st2t(const void *tag)
{
    const struct stivale2_struct_tag_terminal *terminal = tag;
    if(terminal && terminal->term_write) {
        callback = (st2t_write_t)terminal->term_write;
        return 1;
    }

    return 0;
}

void st2t_write(const void *s, size_t n)
{
    if(!callback)
        return;
    callback(s, (uint64_t)n);
}
