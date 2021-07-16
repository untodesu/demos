#include <arch/segment.h>
#include <demos/cdefs.h>
#include <string.h>

struct gdt_ptr {
    uint16_t limit;
    uint64_t base;
} __packed;

static struct gdt_entry gdt[7] = { 0 };
static struct gdt_ptr gdt_ptr = { 0 };

void set_gdt_entry(uint8_t id, const struct gdt_entry *entry)
{
    memcpy(gdt + id, entry, sizeof(struct gdt_entry));
}

void init_gdt(void)
{
    memset(gdt, 0, sizeof(gdt));

    struct gdt_entry entry = { 0 };

    // 16-bit code, base: 0x00000000, limit: 0xFFFFF, 4K: true
    entry.limit_0 = 0xFFFF;
    entry.flags_limit.s.limit_1 = 0xF;
    entry.base_0 = 0x0000;
    entry.base_1 = 0x00;
    entry.base_1 = 0x00;
    entry.access.s.rw = 1;
    entry.access.s.exec = 1;
    entry.access.s.ring = 0;
    entry.access.s.present = 1;
    entry.flags_limit.s.is_4K = 1;
    set_gdt_entry(GDT_INDEX_CODE16, &entry);

    // 16-bit data, base: 0x00000000, limit: 0xFFFFF, 4K: true
    entry.limit_0 = 0xFFFF;
    entry.flags_limit.s.limit_1 = 0xF;
    entry.base_0 = 0x0000;
    entry.base_1 = 0x00;
    entry.base_1 = 0x00;
    entry.access.s.rw = 1;
    entry.access.s.exec = 0;
    entry.access.s.ring = 0;
    entry.access.s.present = 1;
    entry.flags_limit.s.is_4K = 1;
    set_gdt_entry(GDT_INDEX_DATA16, &entry);

    // 32-bit code, base: 0x00000000, limit: 0xFFFFF, 4K: true
    entry.limit_0 = 0xFFFF;
    entry.flags_limit.s.limit_1 = 0xF;
    entry.base_0 = 0x0000;
    entry.base_1 = 0x00;
    entry.base_1 = 0x00;
    entry.access.s.rw = 1;
    entry.access.s.exec = 1;
    entry.access.s.ring = 0;
    entry.access.s.present = 1;
    entry.flags_limit.s.is_32bit = 1;
    entry.flags_limit.s.is_4K = 1;
    set_gdt_entry(GDT_INDEX_CODE32, &entry);

    // 32-bit data, base: 0x00000000, limit: 0xFFFFF, 4K: true
    entry.limit_0 = 0xFFFF;
    entry.flags_limit.s.limit_1 = 0xF;
    entry.base_0 = 0x0000;
    entry.base_1 = 0x00;
    entry.base_1 = 0x00;
    entry.access.s.rw = 1;
    entry.access.s.exec = 0;
    entry.access.s.ring = 0;
    entry.access.s.present = 1;
    entry.flags_limit.s.is_32bit = 1;
    entry.flags_limit.s.is_4K = 1;
    set_gdt_entry(GDT_INDEX_DATA32, &entry);

    // 64-bit code, base: 0x00000000, limit: 0xFFFFF, 4K: true
    entry.limit_0 = 0xFFFF;
    entry.flags_limit.s.limit_1 = 0xF;
    entry.base_0 = 0x0000;
    entry.base_1 = 0x00;
    entry.base_1 = 0x00;
    entry.access.s.rw = 1;
    entry.access.s.exec = 1;
    entry.access.s.ring = 0;
    entry.access.s.present = 1;
    entry.flags_limit.s.is_64bit = 1;
    entry.flags_limit.s.is_4K = 1;
    set_gdt_entry(GDT_INDEX_CODE64, &entry);

    // 64-bit data, base: 0x00000000, limit: 0xFFFFF, 4K: true
    entry.limit_0 = 0xFFFF;
    entry.flags_limit.s.limit_1 = 0xF;
    entry.base_0 = 0x0000;
    entry.base_1 = 0x00;
    entry.base_1 = 0x00;
    entry.access.s.rw = 1;
    entry.access.s.exec = 0;
    entry.access.s.ring = 0;
    entry.access.s.present = 1;
    entry.flags_limit.s.is_64bit = 1;
    entry.flags_limit.s.is_4K = 1;
    set_gdt_entry(GDT_INDEX_DATA64, &entry);

    gdt_ptr.limit = (uint16_t)(sizeof(gdt));
    gdt_ptr.base = (uint64_t)(gdt);

    // This little piece of shit double (or tripple?) faults
    asm volatile(
        "lgdtq %0\n"
        "pushw %1\n"
        "pushq $1f\n"
        "retfq\n"
        "1:\n"
        ::"m"(gdt_ptr), "i"(GDT_SELECTOR(0, 0, GDT_INDEX_CODE64))
    );
}
