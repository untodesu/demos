#ifndef ARCH_VADDR_H
#define ARCH_VADDR_H 1
#include <config.h>

#define virt_to_phys(va) ((va) - CONFIG_X86_BASE_ADDR)
#define phys_to_virt(pa) ((pa) + CONFIG_X86_BASE_ADDR)

#if !defined(__ASSEMBLER__)
#include <arch/stdint.h>
typedef uintptr_t vaddr_t;
typedef uintptr_t paddr_t;
#endif

#endif
