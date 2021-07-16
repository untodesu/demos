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

#define GDT_READWRITE   (1 << 1)
#define GDT_CONFORMING  (1 << 2)
#define GDT_EXECUTABLE  (1 << 3)
#define GDT_NONSYSTEM   (1 << 4)
#define GDT_RING_0      (0 << 5)
#define GDT_RING_3      (3 << 5)

void set_gdt_entry_16(uint8_t id, uint32_t base, uint16_t limit, uint8_t flags);
void set_gdt_entry_32(uint8_t id, uint32_t base, uint32_t limit, uint8_t flags);
void set_gdt_entry_64(uint8_t id, uint8_t flags);
void init_gdt(void);
#endif

#endif
