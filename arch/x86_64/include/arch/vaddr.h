#ifndef ARCH_VADDR_H
#define ARCH_VADDR_H 1

#define KERNEL_VIRTUAL_BASE 0xFFFFFFFF80000000
#define KERNEL_LOAD_ADDRESS 0x0000000000200000

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>
static inline uintptr_t phys_to_virt(uintptr_t x) { return x + KERNEL_VIRTUAL_BASE; }
static inline uintptr_t virt_to_phys(uintptr_t x) { return x - KERNEL_VIRTUAL_BASE; }
#endif

#endif
