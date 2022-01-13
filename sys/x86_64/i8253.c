/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/io.h>
#include <sys/initcall.h>
#include <sys/interrupts.h>
#include <sys/klog.h>
#include <x86/i8253.h>
#include <x86/i8259.h>

#define I8253_CH0 0x40
#define I8253_CMD 0x43

#define I8253_SPEED 1193182

#define I8253_TARGET 14551

static size_t num_ticks = 0;

static void timer_irq(__unused struct interrupt_frame *frame)
{
    num_ticks++;

    /* THIS IS A HACK!!!!! REMOVE THIS AS SOON AS SERIAL DRIVER IS DONE */
    ((volatile uint16_t *)(0xB8000))[num_ticks % (80 * 25)] = num_ticks & 0xFFFF;
}

static int init_i8253(void)
{
    uint16_t divisor = (uint16_t)(I8253_SPEED / I8253_TARGET);
    klog(KLOG_INFO, "i8253: initializing for %u Hz (d: %hu)", I8253_TARGET, divisor);

    num_ticks = 0;

    i8259_unmask_irq(I8259_IRQ_I8253);
    if(!i8259_set_irq_handler(I8259_IRQ_I8253, &timer_irq))
        return 1;

    /* CH0, rate generator, 16-bit binary */
    io_write8(I8253_CMD, 0x34);
    io_write8(I8253_CH0, (divisor & 0x00FF));
    io_write8(I8253_CH0, (divisor & 0xFF00) >> 8);

    return 0;
}

initcall_early(i8253, init_i8253);
initcall_depn(i8253, i8259);
