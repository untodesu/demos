#include <arch/i8253.h>
#include <arch/interrupts.h>
#include <arch/io.h>

#include <arch/serial.h>
#include <demos/string.h>
#include <demos/sprintf.h>

#define PIT_FREQ 1193182
#define PIT_CH0 0x40
#define PIT_CMD 0x43

static uint32_t pit_ticks = 0;

static void pit_intr(struct interrupt_frame *frame)
{
    unused_nw(frame);
    pit_ticks++;

    if(pit_ticks % PIT_TPS == 0) {
        char buffer[64] = { 0 };
        memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, sizeof(buffer), "ds: 0x%08X\n", pit_ticks / PIT_TPS);
        serial_write(0, buffer, strlen(buffer));
    }
}

void init_pit(void)
{
    set_interrupt_handler(0x20, pit_intr);

    uint16_t divisor = PIT_FREQ / PIT_TPS;
    outb(PIT_CMD, 0x34); // ch0, rate generator, 16-bit binary
    outb(PIT_CH0, (divisor & 0x00FF));
    outb(PIT_CH0, (divisor & 0xFF00) >> 8);
}

uint32_t pit_get_ticks(void)
{
    return pit_ticks;
}
