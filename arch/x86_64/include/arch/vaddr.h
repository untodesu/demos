#ifndef ARCH_VADDR_H
#define ARCH_VADDR_H 1
#include <config.h>

#define phys_to_virt(x) ((x) + CONFIG_VIRTUAL_BASE)
#define virt_to_phys(x) ((x) - CONFIG_VIRTUAL_BASE)

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>
typedef uintptr_t paddr_t;
typedef uintptr_t vaddr_t;
#endif

#endif
