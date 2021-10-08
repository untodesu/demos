#include <arch/segment.h>
#include <arch/stdint.h>
#include <demos/cdefs.h>
#include <string.h>

#define SEG_FATTY   (1 << 3) /* Hey hey hey! */
#define SEG_32BIT   (1 << 2)
#define SEG_PRESENT (1 << 7)

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
    uint32_t base;
} __packed;

static struct gdt_entry gdt[4] = { 0 };
static struct gdt_pointer gdt_ptr = { 0 };

void set_segment_entry(uint8_t id, uint32_t base, uint32_t limit, uint8_t flags)
{
    struct gdt_entry entry = { 0 };
    entry.limit_0 = limit & 0xFFFF;
    entry.limit_1 = (limit >> 16) & 0x0F;
    entry.base_0 = base & 0xFFFF;
    entry.base_1 = (base >> 16) & 0xFF;
    entry.base_2 = (base >> 24) & 0xFF;
    entry.flags_0 = flags | SEG_PRESENT;
    entry.flags_1 = SEG_FATTY | SEG_32BIT;
    memcpy(gdt + id, &entry, sizeof(entry));
}

void init_segment(void)
{
    memset(gdt, 0, sizeof(gdt));

    set_segment_entry(SEG_INDEX_K_CODE, 0x00000000, 0xFFFFF, SEG_READWRITE | SEG_NONSYSTEM | SEG_RING_0 | SEG_EXECUTABLE);
    set_segment_entry(SEG_INDEX_K_DATA, 0x00000000, 0xFFFFF, SEG_READWRITE | SEG_NONSYSTEM | SEG_RING_0);
    set_segment_entry(SEG_INDEX_U_CODE, 0x00000000, 0xFFFFF, SEG_READWRITE | SEG_NONSYSTEM | SEG_RING_3 | SEG_EXECUTABLE);
    set_segment_entry(SEG_INDEX_U_DATA, 0x00000000, 0xFFFFF, SEG_READWRITE | SEG_NONSYSTEM | SEG_RING_3);
    
    gdt_ptr.limit = (uint16_t)(sizeof(gdt) - 1);
    gdt_ptr.base = (uint32_t)(&gdt[0]);
    
    asm volatile("lgdtl %0"::"m"(gdt_ptr));
    asm volatile(
        "pushl %0       \n"
        "pushl $1f      \n"
        "retfl          \n"
        "1:             \n"
        "movw %1,   %%ax\n"
        "movw %%ax, %%ds\n"
        "movw %%ax, %%es\n"
        "movw %%ax, %%fs\n"
        "movw %%ax, %%gs\n"
        "movw %%ax, %%ss\n"
        :
        : "i"(SEG_SELECTOR(0, 0, SEG_INDEX_K_CODE)), "i"(SEG_SELECTOR(0, 0, SEG_INDEX_K_DATA))
    );
}
