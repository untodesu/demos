#ifndef __ARCH_ADDRESS_H__
#define __ARCH_ADDRESS_H__ 1
#include <demos/config.h>

#define V2P(va) ((va) - CONFIG_MEM_BASE_ADDR)
#define P2V(pa) ((pa) + CONFIG_MEM_BASE_ADDR)

#endif
