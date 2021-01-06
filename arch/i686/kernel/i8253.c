#include <arch/i8253.h>
#include <arch/interrupts.h>
#include <arch/io.h>

#define PIT_FREQ 1193182
#define PIT_CH0 0x40
#define PIT_CMD 0x43

static uint32_t pit_ticks = 0;

static void pit_intr(struct interrupt_frame *frame)
{
    unused_nw(frame);
    pit_ticks++;
}

void init_pit(void)
{
    set_interrupt_handler(0x20, pit_intr);

    uint16_t divisor = PIT_FREQ / PIT_TPS;
    outb(PIT_CMD, 0x34); // CH0, rate generator, 16-bit binary
    outb(PIT_CH0, (divisor & 0x00FF));
    outb(PIT_CH0, (divisor & 0xFF00) >> 8);
}

uint32_t pit_get_ticks(void)
{
    return pit_ticks;
}
