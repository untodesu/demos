/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/io.h>
#include <sys/initcall.h>
#include <sys/interrupts.h>
#include <sys/klog.h>
#include <sys/panic.h>
#include <x86/i8259.h>

#define I8259_CHIP1 0x20
#define I8259_CHIP2 0xA0

static int irq_enable = 0;
static unsigned int irq_mask = 0;
static interrupt_handler_t irq_handlers[I8250_IRQ_COUNT] = { 0 };

static void common_irq_handler(struct interrupt_frame *frame)
{
    unsigned int irqvector, bit, isr;
    if(frame->vector >= I8259_IRQ_BASE && frame->vector < I8259_IRQ_LIMIT) {
        irqvector = frame->vector - I8259_IRQ_BASE;
        bit = (1 << irqvector);

        /* OCW3: read in-service register */
        io_write8(I8259_CHIP1, 0x0B);
        io_write8(I8259_CHIP2, 0x0B);
        isr = io_read8(I8259_CHIP1) | (io_read8(I8259_CHIP2) << 8);

        if(isr & bit) {
            /* Send EOI */
            if(bit & 0xF0)
                io_write8(I8259_CHIP2, 0x20);
            io_write16(I8259_CHIP1, 0x20);

            /* Call handler */
            if(irqvector != I8259_IRQ_CHIP2 && irq_handlers[irqvector])
                irq_handlers[irqvector](frame);
            return;
        }

        /* There's an imposter among us */
        klog(KLOG_WARN, "i8259: spurious IRQ%u", irqvector);
        return;
    }
}

void i8259_disable_irqs(void)
{
    irq_enable = 0;
    io_write8(I8259_CHIP1 + 1, 0xFF);
    io_write8(I8259_CHIP2 + 1, 0xFF);
}

void i8259_enable_irqs(void)
{
    irq_enable = 1;
    io_write8(I8259_CHIP1 + 1, (irq_mask & 0x00FF));
    io_write8(I8259_CHIP2 + 1, (irq_mask & 0xFF00) >> 8);
}

void i8259_mask_irq(unsigned int irqvector)
{
    unsigned int bit = (1 << irqvector);
    unsigned int shift = (bit & 0xF0) ? 8 : 0;
    io_addr_t port = (bit & 0xF0) ? I8259_CHIP2 : I8259_CHIP1;
    io_write8(port + 1, ((irq_mask |= bit) >> shift) & 0xFF);
}

void i8259_unmask_irq(unsigned int irqvector)
{
    unsigned int bit = (1 << irqvector);
    unsigned int shift = (bit & 0xF0) ? 8 : 0;
    io_addr_t port = (bit & 0xF0) ? I8259_CHIP2 : I8259_CHIP1;
    io_write8(port + 1, ((irq_mask &= ~bit) >> shift) & 0xFF);
}

int i8259_set_irq_handler(unsigned int irqvector, interrupt_handler_t handler)
{
    if(irqvector == I8259_IRQ_CHIP2) {
        klog(KLOG_ERROR, "i8259: IRQ2 not allowed for usage");
        return 0;
    }

    if(irq_handlers[irqvector]) {
        klog(KLOG_ERROR, "i8259: IRQ%u is already claimed!", irqvector);
        return 0;
    }

    irq_handlers[irqvector] = handler;
    i8259_unmask_irq(irqvector);

    return 1;
}

static int init_i8259(void)
{
    unsigned int i;

    /* Claim interrupt vectors */
    for(i = I8259_IRQ_BASE; i < I8259_IRQ_LIMIT; i++) {
        if(set_interrupt_handler(i, &common_irq_handler))
            continue;
        panic("i8259: unable to claim an interrupt vector 0x%02uX", i);
    }

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
    irq_mask = 0xFFFF & ~(1 << I8259_IRQ_CHIP2);
    io_write8(I8259_CHIP1 + 1, irq_mask & 0xFF);
    io_write8(I8259_CHIP2 + 1, (irq_mask >> 8) & 0xFF);

    return 0;
}

initcall_early(i8259, init_i8259);
initcall_depn(i8259, interrupts);
