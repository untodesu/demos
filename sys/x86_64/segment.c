/* SPDX-License-Identifier: BSD-2-Clause */
#include <stdint.h>
#include <sys/init.h>
#include <sys/klog.h>
#include <sys/kstring.h>
#include <x86/segment.h>

#define SEG_READWRITE   (1 << 1)
#define SEG_CONFORMING  (1 << 2)
#define SEG_EXECUTABLE  (1 << 3)
#define SEG_NONSYSTEM   (1 << 4)
#define SEG_RING_0      (0 << 5)
#define SEG_RING_3      (3 << 5)
#define SEG_PRESENT     (1 << 7)
#define SEG_FATTY       (1 << 3) /* Hey hey hey! */
#define SEG_64BIT       (1 << 1)

struct gdt_entry {
    uint16_t limit_0;
    uint16_t base_0;
    uint8_t base_1;
    uint8_t flags_0;
    uint8_t limit_1 : 4;
    uint8_t flags_1 : 4;
    uint8_t base_2;
} __packed;

struct gdt_pointer {
    uint16_t limit;
    uintptr_t base;
} __packed;

static struct gdt_entry gdt[16] = { 0 };
static struct gdt_pointer gdt_ptr = { 0 };

void set_entry(uint8_t id, uint8_t flags)
{
    struct gdt_entry entry = { 0 };
    entry.flags_0 = flags | SEG_PRESENT;
    entry.flags_1 = SEG_64BIT;
    memcpy(gdt + id, &entry, sizeof(entry));
}

static int init_seg(void)
{
    uint8_t code_flags = SEG_READWRITE | SEG_NONSYSTEM | SEG_EXECUTABLE;
    uint8_t data_flags = SEG_READWRITE | SEG_NONSYSTEM;

    memset(gdt, 0, sizeof(gdt));

    set_entry(SEG_INDEX_KERN_CODE, code_flags | SEG_RING_0);
    set_entry(SEG_INDEX_KERN_DATA, data_flags | SEG_RING_0);
    set_entry(SEG_INDEX_USER_CODE, code_flags | SEG_RING_3);
    set_entry(SEG_INDEX_USER_DATA, data_flags | SEG_RING_3);

    gdt_ptr.limit = (uint16_t)(sizeof(gdt) - 1);
    gdt_ptr.base = (uintptr_t)(&gdt[0]);

    klog(KLOG_INF, "gdt: limit=%hu, base=%p", gdt_ptr.limit, (void *)gdt_ptr.base);

    asm volatile("lgdtq %0"::"m"(gdt_ptr));
    asm volatile(
        "movw %1,   %%ax\n"
        "movw %%ax, %%ds\n"
        "movw %%ax, %%es\n"
        "movw %%ax, %%fs\n"
        "movw %%ax, %%gs\n"
        "movw %%ax, %%ss\n"
        "pushq %0       \n"
        "pushq $1f      \n"
        "retfq          \n"
        "1:             \n"
        :
        : "i"(SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0)), "i"(SEG_SELECTOR(SEG_INDEX_KERN_DATA, 0, 0))
    );

    return 0;
}

extern_initcall(klog);
early_initcall(segment, init_seg);
initcall_dependency(segment, klog);
