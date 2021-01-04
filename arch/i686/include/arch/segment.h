#ifndef __ARCH_SEGMENT_H__
#define __ARCH_SEGMENT_H__ 1

#define GDT_SELECTOR(r, t, i) (((r) & 3) | (((t) & 1) << 2) | ((i) << 3))

#define GDT_BOOT_NULL (0x0000000000000000)
#define GDT_BOOT_CODE (0x00CF9A000000FFFF)
#define GDT_BOOT_DATA (0x00CF92000000FFFF)

#endif
