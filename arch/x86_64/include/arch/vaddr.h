/* NOTENOTE: this would be changed to mm.h
 * with according offsets. Also vaddr->paddr
 * and back conversion should be done with a
 * different offset as I can see in QWord... */
#ifndef _ARCH_VADDR_H_
#define _ARCH_VADDR_H_ 1

#define KERNEL_VIRTUAL_BASE 0xFFFFFFFF80000000
#define KERNEL_LOAD_ADDRESS 0x0000000000200000

#if !defined(__ASSEMBLER__)
#include <stdint.h>
static inline uintptr_t phys_to_virt(uintptr_t x) { return x + KERNEL_VIRTUAL_BASE; }
static inline uintptr_t virt_to_phys(uintptr_t x) { return x - KERNEL_VIRTUAL_BASE; }
#endif

#endif
