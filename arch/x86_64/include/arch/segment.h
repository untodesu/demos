#ifndef ARCH_SEGMENT_H
#define ARCH_SEGMENT_H 1

#define GDT_INDEX_NULL (0)
#define GDT_INDEX_CODE16 (1)
#define GDT_INDEX_DATA16 (2)
#define GDT_INDEX_CODE32 (3)
#define GDT_INDEX_DATA32 (4)
#define GDT_INDEX_CODE64 (5)
#define GDT_INDEX_DATA64 (6)

#define GDT_SELECTOR(r, t, i) (((r) & 3) | (((t) & 1) << 2) | ((i) << 3))

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>

struct gdt_entry {
    uint16_t limit_0;
    uint16_t base_0;
    uint8_t base_1;
    union {
        uint8_t b;
        struct {
            uint8_t ac : 1;
            uint8_t rw : 1;
            uint8_t down : 1;
            uint8_t exec : 1;
            uint8_t user : 1;
            uint8_t ring : 2;
            uint8_t present : 1;
        } s;
    } access;
    union {
        uint8_t b;
        struct {
            uint8_t limit_1 : 4;
            uint8_t reserved : 1;
            uint8_t is_64bit : 1;
            uint8_t is_32bit : 1;
            uint8_t is_4K : 1;
        } s;
    } flags_limit;
    uint8_t base_2;
} __packed;

void set_gdt_entry(uint8_t id, const struct gdt_entry *entry);
void init_gdt(void);
#endif

#endif
