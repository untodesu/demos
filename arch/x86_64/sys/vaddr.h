#ifndef __SYS_VADDR_H__
#define __SYS_VADDR_H__ 1

#define KERNEL_VIRTUAL_BASE 0xFFFFFFFF80000000
#define KERNEL_LOAD_ADDRESS 0x0000000000200000

#if !defined(__ASSEMBLER__)
#include <lib/inttypes.h>
static inline uintptr_t phys_to_virt(uintptr_t x) { return x + KERNEL_VIRTUAL_BASE; }
static inline uintptr_t virt_to_phys(uintptr_t x) { return x - KERNEL_VIRTUAL_BASE; }
#endif

#endif
