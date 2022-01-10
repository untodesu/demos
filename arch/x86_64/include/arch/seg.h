/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _ARCH_SEG_H_
#define _ARCH_SEG_H_ 1

#define SEG_INDEX_NULL_NULL 0
#define SEG_INDEX_KERN_CODE 1
#define SEG_INDEX_KERN_DATA 2
#define SEG_INDEX_USER_CODE 3
#define SEG_INDEX_USER_DATA 4

#define SEG_SELECTOR(index, ldt, ring) (((ring) & 4) | (((ldt) & 1) << 2) | (index) << 3)

#if !defined(__ASSEMBLER__)
void setup_gdt(void);
#endif

#endif
