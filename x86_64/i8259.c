/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/io.h>
#include <sys/initcall.h>
#include <sys/intr.h>
#include <sys/printk.h>
#include <x86/i8259.h>

#define I8259_CHIP1 0x20
#define I8259_CHIP2 0xA0

static unsigned int mask = 0;
static intr_handler_t handlers[I8250_IRQ_COUNT] = { 0 };

static void common_irq_handler(struct intr_frame *frame, void *data)
{
    unsigned int irqvector = frame->vector - I8259_IRQ_BASE;
    unsigned int bit = (1 << irqvector);
    unsigned int isr;

    /* OCW3 - read in-service register */
    io_write8(I8259_CHIP1, 0x0B);
    io_write8(I8259_CHIP2, 0x0B);
    isr = io_read8(I8259_CHIP1) | (io_read8(I8259_CHIP2) << 8);

    /* There's an imposter among us */
    if(!(isr & bit)) {
        pk_notice("8259: spurious IRQ%u", irqvector);
        return;
    }

    if(handlers[irqvector])
        handlers[irqvector](frame, data);

    /* Send EoI */
    if(bit & 0xF0)
        io_write8(I8259_CHIP2, 0x20);
    io_write16(I8259_CHIP1, 0x20);
}

void i8259_disable_irqs(void)
{
    io_write8(I8259_CHIP1 + 1, 0xFF);
    io_write8(I8259_CHIP2 + 1, 0xFF);
}

void i8259_enable_irqs(void)
{
    io_write8(I8259_CHIP1 + 1, (mask & 0x00FF));
    io_write8(I8259_CHIP2 + 1, (mask & 0xFF00) >> 8);
}

void i8259_mask_irq(unsigned int irqvector)
{
    unsigned int bit = (1 << irqvector);
    unsigned int shift = (bit & 0xF0) ? 8 : 0;
    io_addr_t port = (bit & 0xF0) ? I8259_CHIP2 : I8259_CHIP1;
    io_write8(port + 1, ((mask |= bit) >> shift) & 0xFF);
}

void i8259_unmask_irq(unsigned int irqvector)
{
    unsigned int bit = (1 << irqvector);
    unsigned int shift = (bit & 0xF0) ? 8 : 0;
    io_addr_t port = (bit & 0xF0) ? I8259_CHIP2 : I8259_CHIP1;
    io_write8(port + 1, ((mask &= ~bit) >> shift) & 0xFF);
}

int i8259_set_irq_handler(unsigned int irqvector, intr_handler_t func, void *data)
{
    if(irqvector == I8259_IRQ_CHIP2) {
        pk_warn("8259: IRQ2 not allowed");
        return 0;
    }

    handlers[irqvector] = func;

    set_intr_handler(I8259_IRQ_BASE + irqvector, &common_irq_handler, data);

    return 1;
}

static void init_i8259(void)
{
    /* Mask everything */
    io_write8(I8259_CHIP1 + 1, 0xFF);
    io_write8(I8259_CHIP2 + 1, 0xFF);

    /* ICW1 - start initializing */
    io_write8(I8259_CHIP1, (1 << 4) | (1 << 0));
    io_write8(I8259_CHIP2, (1 << 4) | (1 << 0));

    /* ICW2 - new vector offsets */
    io_write8(I8259_CHIP1 + 1, I8259_IRQ_BASE + 0);
    io_write8(I8259_CHIP2 + 1, I8259_IRQ_BASE + 8);

    /* ICW3 - cascade IRQ2 to the second chip */
    io_write8(I8259_CHIP1 + 1, (1 << 2));
    io_write8(I8259_CHIP2 + 1, (1 << 1));
    
    /* ICW4 - switch to 8086/88 mode */
    io_write8(I8259_CHIP1 + 1, (1 << 0));
    io_write8(I8259_CHIP2 + 1, (1 << 0));

    /* Mask everything except cascading IRQ */
    mask = 0xFFFF & ~(1 << I8259_IRQ_CHIP2);
    io_write8(I8259_CHIP1 + 1, mask & 0xFF);
    io_write8(I8259_CHIP2 + 1, (mask >> 8) & 0xFF);

    /* Call to this results in a mask upload */
    i8259_enable_irqs();
}

boot_initcall(i8259, init_i8259);
initcall_dependency(i8259, intrs);
