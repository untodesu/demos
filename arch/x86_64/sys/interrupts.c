#include <drivers/i8259.h>
#include <lib/compiler.h>
#include <lib/string.h>
#include <sys/interrupts.h>
#include <sys/segment.h>

#define IDT_TRAP_GATE   (0x0F << 0)
#define IDT_PRESENT     (0x01 << 7)

struct idt_entry {
    uint16_t offset_0;
    uint16_t selector;
    uint8_t ist_off;
    uint8_t flags;
    uint16_t offset_1;
    uint32_t offset_2;
    uint32_t reserved;
} __packed;

struct idt_pointer {
    uint16_t limit;
    uintptr_t base;
} __packed;

static struct idt_entry idt[256] = { 0 };
static struct idt_pointer idt_ptr = { 0 };

void init_interrupts(void)
{
    memset(idt, 0, sizeof(idt));
    idt_ptr.limit = (uint16_t)(sizeof(idt) - 1);
    idt_ptr.base = (uintptr_t)(&idt[0]);
    asm volatile("lidtq %0"::"m"(idt_ptr));
}

void set_interrupt_handler(unsigned int vector, uintptr_t offset, int level)
{
    struct idt_entry entry = { 0 };
    entry.offset_0 = offset & 0xFFFF;
    entry.offset_1 = (offset >> 16) & 0xFFFF;
    entry.offset_2 = (offset >> 32) & 0xFFFFFFFF;
    entry.selector = SEG_SELECTOR(SEG_INDEX_CODE64, 0, 0);
    entry.flags = IDT_PRESENT | IDT_TRAP_GATE | ((level & 0x04) << 5);
    memcpy(idt + (vector & 0xFF), &entry, sizeof(entry));
}
