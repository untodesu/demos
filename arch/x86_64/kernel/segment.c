#include <arch/segment.h>
#include <arch/stdint.h>
#include <demos/cdefs.h>
#include <string.h>

#define GDT_FATTY   (1 << 3)
#define GDT_32BIT   (1 << 2)
#define GDT_64BIT   (1 << 1)
#define GDT_PRESENT (1 << 7)

struct gdt_entry {
    uint16_t limit_0;
    uint16_t base_0;
    uint8_t base_1;
    uint8_t flags_0;
    uint8_t limit_1 : 4;
    uint8_t flags_1 : 4;
    uint8_t base_2;
} __packed;

struct gdt_pointer {
    uint16_t limit;
    uint64_t base;
} __packed;

static struct gdt_entry gdt[7] = { 0 };
static struct gdt_pointer gdt_ptr = { 0 };

void set_gdt_entry_16(uint8_t id, uint32_t base, uint16_t limit, uint8_t flags)
{
    struct gdt_entry entry = { 0 };
    entry.limit_0 = limit;
    entry.base_0 = base & 0xFFFF;
    entry.base_1 = (base >> 16) & 0xFF;
    entry.base_2 = (base >> 24) & 0xFF;
    entry.flags_0 = flags | GDT_PRESENT;
    memcpy(gdt + id, &entry, sizeof(entry));
}

void set_gdt_entry_32(uint8_t id, uint32_t base, uint32_t limit, uint8_t flags)
{
    struct gdt_entry entry = { 0 };
    entry.limit_0 = limit;
    entry.limit_1 = (limit >> 16) & 0x0F;
    entry.base_0 = base & 0xFFFF;
    entry.base_1 = (base >> 16) & 0xFF;
    entry.base_2 = (base >> 24) & 0xFF;
    entry.flags_0 = flags | GDT_PRESENT;
    entry.flags_1 = GDT_FATTY | GDT_32BIT;
    memcpy(gdt + id, &entry, sizeof(entry));
}

void set_gdt_entry_64(uint8_t id, uint8_t flags)
{
    struct gdt_entry entry = { 0 };
    entry.flags_0 = flags | GDT_PRESENT;
    entry.flags_1 = GDT_64BIT;
    memcpy(gdt + id, &entry, sizeof(entry));
}

void init_gdt(void)
{
    set_gdt_entry_16(GDT_INDEX_CODE16, 0x00000000, 0xFFFF, GDT_READWRITE | GDT_NONSYSTEM | GDT_RING_0 | GDT_EXECUTABLE);
    set_gdt_entry_16(GDT_INDEX_DATA16, 0x00000000, 0xFFFF, GDT_READWRITE | GDT_NONSYSTEM | GDT_RING_0);
    set_gdt_entry_32(GDT_INDEX_CODE32, 0x00000000, 0xFFFFF, GDT_READWRITE | GDT_NONSYSTEM | GDT_RING_0 | GDT_EXECUTABLE);
    set_gdt_entry_32(GDT_INDEX_DATA32, 0x00000000, 0xFFFFF, GDT_READWRITE | GDT_NONSYSTEM | GDT_RING_0);
    set_gdt_entry_64(GDT_INDEX_CODE64, GDT_READWRITE | GDT_NONSYSTEM | GDT_RING_0 | GDT_EXECUTABLE);
    set_gdt_entry_64(GDT_INDEX_DATA64, GDT_READWRITE | GDT_NONSYSTEM | GDT_RING_0);

    gdt_ptr.limit = (uint16_t)(sizeof(gdt) - 1);
    gdt_ptr.base = (uint64_t)(gdt);

    asm volatile("lgdtq %0"::"m"(gdt_ptr));
    asm volatile(
        "mov %1, %%ax   \n"
        "mov %%ax, %%ds \n"
        "mov %%ax, %%es \n"
        "mov %%ax, %%fs \n"
        "mov %%ax, %%gs \n"
        "mov %%ax, %%ss \n"
        "pushq %0       \n"
        "pushq $1f      \n"
        "retfq          \n"
        "1:             \n"
        :
        : "i"(GDT_SELECTOR(0, 0, GDT_INDEX_CODE64)), "i"(GDT_SELECTOR(0, 0, GDT_INDEX_DATA64))
    );
}