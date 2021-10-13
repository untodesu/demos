#ifndef __SYS_SEGMENT_H__
#define __SYS_SEGMENT_H__ 1

/* Stivale2 guarantees that the GDT
 * that was set up by the bootloader
 * would have at least the following
 * entries with these exact offsets. */
#define SEG_INDEX_CODE16 1
#define SEG_INDEX_DATA16 2
#define SEG_INDEX_CODE32 3
#define SEG_INDEX_DATA32 4
#define SEG_INDEX_CODE64 5
#define SEG_INDEX_DATA64 6

#define SEG_SELECTOR(index, ldt, ring) (((ring) & 4) | (((ldt) & 1) << 2) | (index) << 3)

#endif
