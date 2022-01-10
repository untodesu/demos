/* SPDX-License-Identifier: BSD-2-Clause */
#include <arch/i8259.h>
#include <arch/io.h>
#include <sys/klog.h>

#define I8259_PORT_1        0x20
#define I8259_PORT_2        0xA0
#define I8259_CASCADE_IRQ   0x02

static unsigned int mask = 0;

static inline unsigned int read_isr(void)
{
    io_write8(I8259_PORT_1, 0x0B);
    io_write8(I8259_PORT_2, 0x0B);
    return (io_read8(I8259_PORT_2) << 8) | io_read8(I8259_PORT_1);
}

void init_i8259(void)
{
    /* Mask everything */
    io_write8(I8259_PORT_1 + 1, 0xFF);
    io_write8(I8259_PORT_2 + 1, 0xFF);

    /* ICW1 - start initializing */
    io_write8(I8259_PORT_1, (1 << 4) | (1 << 0));
    io_write8(I8259_PORT_2, (1 << 4) | (1 << 0));

    /* ICW2 - new vector offsets */
    io_write8(I8259_PORT_1 + 1, I8259_IRQ(0x00));
    io_write8(I8259_PORT_2 + 1, I8259_IRQ(0x08));

    /* ICW3 - cascade IRQ2 to the second chip */
    io_write8(I8259_PORT_1 + 1, (1 << 2));
    io_write8(I8259_PORT_2 + 1, (1 << 1));
    
    /* ICW4 - switch to 8086/88 mode */
    io_write8(I8259_PORT_1 + 1, (1 << 0));
    io_write8(I8259_PORT_2 + 1, (1 << 0));

    /* Mask everything except cascading IRQ */
    mask = 0xFFFF & ~(1 << I8259_CASCADE_IRQ);
    io_write8(I8259_PORT_1 + 1, mask & 0xFF);
    io_write8(I8259_PORT_2 + 1, (mask >> 8) & 0xFF);
}

void i8259_mask(unsigned int irq, int set)
{
    unsigned int bit = (1 << irq);
    unsigned int shift = (bit & 0xF0) ? 8 : 0;
    uint16_t port = (bit & 0xF0) ? I8259_PORT_2 : I8259_PORT_1;
    mask = set ? (mask | bit) : (mask & ~bit);
    io_write8(port + 1, (mask >> shift) & 0xFF);
}

int i8259_send_eoi(unsigned int irq)
{
    unsigned int bit = (1 << irq);
    if(read_isr() & bit) {
        if(bit & 0xF0)
            io_write8(I8259_PORT_2, 0x20);
        io_write8(I8259_PORT_1, 0x20);
        return 1;
    }

    /* There's an imposter among us */
    klog(KLOG_WARN, "i8259: spurious IRQ %u", irq);
    return 0;
}
