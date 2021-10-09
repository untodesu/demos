#include <arch/drivers/i8253.h>
#include <arch/drivers/i8259.h>
#include <arch/interrupts.h>
#include <arch/io.h>
#include <demos/kprintf.h>

#define I8253_FREQ  (1193182)
#define I8253_CH0   (0x40)
#define I8253_CMD   (0x43)

static uint64_t num_ticks = 0;

static void irq_0_handler(struct interrupt_frame *frame)
{
    (void)(frame);
    num_ticks++;
    if(!(num_ticks % I8253_SPEED))
        kprintf("i8253: %llus\r\n", num_ticks / I8253_SPEED);
}

void init_i8253(void)
{
    /* I8253 (PIT) triggers IRQ0 on I8259 */
    set_interrupt_handler(I8259_IRQ0 + 0x00, irq_0_handler);

    uint16_t divisor = (uint16_t)(I8253_FREQ / I8253_SPEED);
    kprintf("i8253: initializing for %u Hz (d: %hu)\r\n", I8253_SPEED, divisor);

    /* CH0, rate generator, 16-bit binary */
    outb(I8253_CMD, 0x34);
    outb(I8253_CH0, (divisor & 0x00FF));
    outb(I8253_CH0, (divisor & 0xFF00) >> 8);
}

uint64_t i8253_ticks(void)
{
    return num_ticks;
}
