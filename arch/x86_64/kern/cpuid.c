#include <arch/cpuid.h>
#include <inttypes.h>
#include <string.h>

#define CPUID_EAX 0
#define CPUID_EBX 1
#define CPUID_EDX 2
#define CPUID_ECX 3

static inline void cpuid(uint32_t input, uint32_t output[4])
{
    asm volatile("cpuid":"=a"(output[CPUID_EAX]), "=b"(output[CPUID_EBX]), "=d"(output[CPUID_EDX]), "=c"(output[CPUID_ECX]):"a"(input));
}

static uint32_t max_standard = 0;
static char vendor_string[16] = { 0 };

void init_cpuid(void)
{
    uint32_t output[4] = { 0 };
    cpuid(0x00000000, output);

    /* maximum supported standard level */
    max_standard = output[CPUID_EAX];

    /* vendor ID string */
    memset(vendor_string, 0, sizeof(vendor_string));
    memcpy(vendor_string, output + 1, sizeof(uint32_t) * 3);
}

const char *cpuid_get_vendor(void)
{
    return vendor_string;
}
