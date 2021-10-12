#include <mm/pmm.h>
#include <sys/panic.h>
#include <sys/stivale2.h>

void init_pmm(__unused const struct stivale2_struct_tag_memmap *tag)
{
    panic("pmm: not implemented :)");
}
