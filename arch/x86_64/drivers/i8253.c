#include <drivers/i8253.h>
#include <drivers/i8259.h>
#include <sys/interrupts.h>
#include <sys/kprintf.h>
#include <sys/ports.h>

#define I8253_CH0 0x40
#define I8253_CMD 0x43
#define I8253_FRQ 1193182
#define I8253_IRQ 0x00

static uint64_t num_ticks = 0;

static void __interrupt i8253_irq_handler(__unused struct interrupt_frame *frame)
{
    i8259_send_eoi(I8253_IRQ);
    i8259_mask(I8253_IRQ, 1);

    num_ticks++;

    if(num_ticks % I8253_SPEED == 0)
        kprintf("i8253: %llus\r\n", num_ticks / I8253_SPEED);
    
    i8259_mask(I8253_IRQ, 0);
}

void init_i8253(void)
{
    uint16_t divisor = (uint16_t)(I8253_FRQ / I8253_SPEED);
    kprintf("i8253: initializing for %u Hz (d: %hu)\r\n", I8253_SPEED, divisor);

    /* I8253 (PIT) triggers IRQ0 on I8259 */
    i8259_mask(I8253_IRQ, 0);
    set_interrupt_handler(I8259_IRQ(I8253_IRQ), (uintptr_t)(&i8253_irq_handler), 0);

    /* CH0, rate generator, 16-bit binary */
    outb(I8253_CMD, 0x34);
    outb(I8253_CH0, (divisor & 0x00FF));
    outb(I8253_CH0, (divisor & 0xFF00) >> 8);
}

uint64_t i8253_ticks(void)
{
    return num_ticks;
}
