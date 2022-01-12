/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/io.h>
#include <sys/interrupt.h>
#include <sys/klog.h>
#include <x86/i8253.h>
#include <x86/i8259.h>

#define I8253_CH0 0x40
#define I8253_CMD 0x43
#define I8253_FRQ 1193182
#define I8253_IRQ 0x00

static size_t num_ticks = 0;

static void i8253_irq_handler(__unused struct interrupt_frame *frame)
{
    if(i8259_send_eoi(I8253_IRQ)) {
        i8259_mask(I8253_IRQ, 1);
        num_ticks++;
        if(num_ticks % I8253_SPEED == 0)
            klog(KLOG_DBG, "i8253: %zus", num_ticks / I8253_SPEED);

        /* THIS IS A HACK!!!!! REMOVE THIS AS SOON AS SERIAL DRIVER IS DONE */
        ((volatile uint16_t *)(0xB8000))[0] = num_ticks & 0xFFFF;

        i8259_mask(I8253_IRQ, 0);
    }
}

void init_i8253(void)
{
    uint16_t divisor = (uint16_t)(I8253_FRQ / I8253_SPEED);
    klog(KLOG_INF, "i8253: initializing for %u Hz (d: %hu)", I8253_SPEED, divisor);

    num_ticks = 0;

    /* I8253 (PIT) triggers IRQ0 on I8259 */
    i8259_mask(I8253_IRQ, 0);
    set_interrupt_handler(I8259_IRQ(I8253_IRQ), &i8253_irq_handler);

    /* CH0, rate generator, 16-bit binary */
    io_write8(I8253_CMD, 0x34);
    io_write8(I8253_CH0, (divisor & 0x00FF));
    io_write8(I8253_CH0, (divisor & 0xFF00) >> 8);
}

size_t i8253_ticks(void)
{
    return num_ticks;
}
