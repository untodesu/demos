#include <arch/drivers/i8253.h>
#include <arch/drivers/i8259.h>
#include <arch/interrupts.h>
#include <arch/io.h>
#include <demos/kprintf.h>

#define I8253_FREQ  (1193182)
#define I8253_CH0   (0x40)
#define I8253_CMD   (0x43)

static uint64_t num_ticks = 0;

static void i8253_irq(struct interrupt_frame *frame)
{
    (void)(frame);
    num_ticks++;
}

void init_i8253(void)
{
    set_interrupt_handler(I8259_IRQ0 + 0x00, i8253_irq);

    uint16_t divisor = I8253_FREQ / I8253_SPEED;
    kprintf("i8253: initializing for %u Hz (d: %hu)\r\n", I8253_SPEED, divisor);

    outb(I8253_CMD, 0x34); /* CH0, rate generator, 16-bit binary */
    outb(I8253_CH0, (divisor & 0x00FF));
    outb(I8253_CH0, (divisor & 0xFF00) >> 8);
}

uint64_t i8253_ticks(void)
{
    return num_ticks;
}
