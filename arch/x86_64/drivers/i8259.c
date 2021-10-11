#include <drivers/i8259.h>
#include <sys/kprintf.h>
#include <sys/ports.h>

#define I8259_PORT_1        0x20
#define I8259_PORT_2        0xA0
#define I8259_CASCADE_IRQ   0x02

static unsigned int mask = 0;

static inline unsigned int read_isr(void)
{
    outb(I8259_PORT_1, 0x0B);
    outb(I8259_PORT_2, 0x0B);
    return (inb(I8259_PORT_2) << 8) | inb(I8259_PORT_1);
}

void init_i8259(void)
{
    /* Mask everything */
    outb(I8259_PORT_1 + 1, 0xFF);
    outb(I8259_PORT_2 + 1, 0xFF);

    /* ICW1 - start initializing */
    outb(I8259_PORT_1, (1 << 4) | (1 << 0));
    outb(I8259_PORT_2, (1 << 4) | (1 << 0));

    /* ICW2 - new vector offsets */
    outb(I8259_PORT_1 + 1, I8259_IRQ(0x00));
    outb(I8259_PORT_2 + 1, I8259_IRQ(0x08));

    /* ICW3 - cascade IRQ2 to the second chip */
    outb(I8259_PORT_1 + 1, (1 << 2));
    outb(I8259_PORT_2 + 1, (1 << 1));
    
    /* ICW4 - switch to 8086/88 mode */
    outb(I8259_PORT_1 + 1, (1 << 0));
    outb(I8259_PORT_2 + 1, (1 << 0));

    /* Mask everything except cascading IRQ */
    mask = 0xFFFF & ~(1 << I8259_CASCADE_IRQ);
    outb(I8259_PORT_1 + 1, mask & 0xFF);
    outb(I8259_PORT_2 + 1, (mask >> 8) & 0xFF);
}

void i8259_mask(unsigned int irq, int set)
{
    unsigned int bit = (1 << irq);
    unsigned int shift = (bit & 0xF0) ? 8 : 0;
    uint16_t port = (bit & 0xF0) ? I8259_PORT_2 : I8259_PORT_1;
    mask = set ? (mask | bit) : (mask & ~bit);
    outb(port + 1, (mask >> shift) & 0xFF);
}

void i8259_send_eoi(unsigned int irq)
{
    unsigned int bit = (1 << irq);
    if(read_isr() & bit) {
        if(bit & 0xF0)
            outb(I8259_PORT_2, 0x20);
        outb(I8259_PORT_1, 0x20);
        return;
    }

    /* There's an imposter among us */
    kprintf("i8259: warning: spurious IRQ %u", irq);
}
