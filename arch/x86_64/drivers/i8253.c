#include <sys/drivers/i8253.h>
#include <sys/drivers/i8259.h>
#include <sys/interrupts.h>
#include <sys/kprintf.h>
#include <sys/ports.h>

#define I8253_FREQ  1193182
#define I8253_CH0   0x40
#define I8253_CMD   0x43

static uint64_t num_ticks = 0;

static void irq_0_handler(__unused struct interrupt_frame *frame)
{
    num_ticks++;

    if(num_ticks % I8253_SPEED == 0)
        kprintf("i8253: %llus\r\n", num_ticks / I8253_SPEED);
}

void init_i8253(void)
{
    uint16_t divisor = (uint16_t)(I8253_FREQ / I8253_SPEED);
    kprintf("i8253: initializing for %u Hz (d: %hu)\r\n", I8253_SPEED, divisor);

    /* I8253 (PIT) triggers IRQ0 on I8259 */
    set_interrupt_handler(I8259_IRQ0 + 0x00, irq_0_handler);

    /* CH0, rate generator, 16-bit binary */
    outb(I8253_CMD, 0x34);
    outb(I8253_CH0, (divisor & 0x00FF));
    outb(I8253_CH0, (divisor & 0xFF00) >> 8);
}

uint64_t i8253_ticks(void)
{
    return num_ticks;
}
