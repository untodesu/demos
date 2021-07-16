#ifndef ARCH_SEGMENT_H
#define ARCH_SEGMENT_H 1

#define SEG_INDEX_NULL (0)
#define SEG_INDEX_CODE16 (1)
#define SEG_INDEX_DATA16 (2)
#define SEG_INDEX_CODE32 (3)
#define SEG_INDEX_DATA32 (4)
#define SEG_INDEX_CODE64 (5)
#define SEG_INDEX_DATA64 (6)

#define SEG_SELECTOR(r, t, i) (((r) & 3) | (((t) & 1) << 2) | ((i) << 3))

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>

#define SEG_READWRITE   (1 << 1)
#define SEG_CONFORMING  (1 << 2)
#define SEG_EXECUTABLE  (1 << 3)
#define SEG_NONSYSTEM   (1 << 4)
#define SEG_RING_0      (0 << 5)
#define SEG_RING_3      (3 << 5)

void set_segment_entry_16(uint8_t id, uint32_t base, uint16_t limit, uint8_t flags);
void set_segment_entry_32(uint8_t id, uint32_t base, uint32_t limit, uint8_t flags);
void set_segment_entry_64(uint8_t id, uint8_t flags);
void init_segment(void);
#endif

#endif
