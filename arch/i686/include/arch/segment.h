#ifndef ARCH_SEGMENT_H
#define ARCH_SEGMENT_H 1

/* These pre-defined segments are put to the early GDT
 * before mapping the kernel to the higher address and
 * are here just to prevent any potential trollge incidents. */
#define SEG_BOOT_NULL (0x0000000000000000)
#define SEG_BOOT_CODE (0x00CF9A000000FFFF)
#define SEG_BOOT_DATA (0x00CF92000000FFFF)

#define SEG_INDEX_NULL      (0)
#define SEG_INDEX_K_CODE    (1)
#define SEG_INDEX_K_DATA    (2)
#define SEG_INDEX_U_CODE    (3)
#define SEG_INDEX_U_DATA    (4)

#define SEG_SELECTOR(ring, ldt, index) (((ring) & 3) | (((ldt) & 1) << 2) | ((index) << 3))

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>

#define SEG_READWRITE   (1 << 1)
#define SEG_CONFORMING  (1 << 2)
#define SEG_EXECUTABLE  (1 << 3)
#define SEG_NONSYSTEM   (1 << 4)
#define SEG_RING_0      (0 << 5)
#define SEG_RING_3      (3 << 5)

void set_segment_entry(uint8_t id, uint32_t base, uint32_t limit, uint8_t flags);
void init_segment(void);
#endif

#endif
