/* SPDX-License-Identifier: BSD-2-Clause */
#include <stddef.h>
#include <sys/io.h>
#include <sys/initcall.h>
#include <sys/intr.h>
#include <sys/printk.h>
#include <x86/i8253.h>
#include <x86/i8259.h>

#define I8253_CH0 0x40
#define I8253_CMD 0x43

#define I8253_SPEED 1193182

#define I8253_TARGET 14551

static size_t num_ticks = 0;

static void irq_i8253(__unused struct interrupt_frame *frame, __unused void *data)
{
    num_ticks++;
    if(num_ticks % I8253_TARGET == 0)
        pk_debug("i8253: %zus", num_ticks / I8253_TARGET);
    ((volatile uint16_t *)(0xB8000))[num_ticks % (80 * 25)] = num_ticks & 0xFFFF;
}

static int init_i8253(void)
{
    uint16_t divisor = (uint16_t)(I8253_SPEED / I8253_TARGET);
    pk_debug("i8253: divisor=%hu", divisor);

    num_ticks = 0;

    i8259_set_irq_handler(I8259_IRQ_I8253, &irq_i8253, NULL);
    i8259_unmask_irq(I8259_IRQ_I8253);

    /* CH0, rate generator, 16-bit binary */
    io_write8(I8253_CMD, 0x34);
    io_write8(I8253_CH0, (divisor & 0x00FF));
    io_write8(I8253_CH0, (divisor & 0xFF00) >> 8);

    return 0;
}

boot_initcall(i8253, init_i8253);
initcall_dependency(i8253, i8259);
