#ifndef ARCH_SEGMENT_H
#define ARCH_SEGMENT_H 1

/* These pre-defined segments are put to the early GDT
 * before mapping the kernel to the higher address and
 * are here just to prevent any potential trollge incidents. */
#define SEG_BOOT_NULL (0x0000000000000000)
#define SEG_BOOT_CODE (0x00CF9A000000FFFF)
#define SEG_BOOT_DATA (0x00CF92000000FFFF)

#if defined(X86_64)
#define SEG_INDEX_NULL      (0)
#define SEG_INDEX_CODE16    (1)
#define SEG_INDEX_DATA16    (2)
#define SEG_INDEX_CODE32    (3)
#define SEG_INDEX_DATA32    (4)
#define SEG_INDEX_CODE64    (5)
#define SEG_INDEX_DATA64    (6)
#else
#define SEG_INDEX_NULL      (0)
#define SEG_INDEX_K_CODE    (1)
#define SEG_INDEX_K_DATA    (2)
#define SEG_INDEX_U_CODE    (3)
#define SEG_INDEX_U_DATA    (4)
#endif

#define SEG_SELECTOR(ring, ldt, index) (((ring) & 3) | (((ldt) & 1) << 2) | ((index) << 3))

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>

void init_segment(void);
#endif

#endif
