#include <arch/drivers/i8259.h>
#include <arch/io.h>

#define I8259_PORT_1 (0x20)
#define I8259_PORT_2 (0xA0)

static uint8_t mask_1 = 0xFF & ~(1 << 2);
static uint8_t mask_2 = 0xFF;

void init_i8259(void)
{
    outb(I8259_PORT_1 + 0, 0x11);
    outb(I8259_PORT_2 + 0, 0x11);
    outb(I8259_PORT_1 + 1, I8259_IRQ0);
    outb(I8259_PORT_2 + 1, I8259_IRQ8);
    outb(I8259_PORT_1 + 1, 0x04);
    outb(I8259_PORT_2 + 1, 0x02);
    outb(I8259_PORT_1 + 1, 0x01);
    outb(I8259_PORT_2 + 1, 0x01);
    outb(I8259_PORT_1 + 1, mask_1);
    outb(I8259_PORT_2 + 1, mask_2);
}

void i8259_mask(uint8_t irq)
{
    uint16_t port;
    uint8_t *mask;
    if(irq < 8) {
        port = I8259_PORT_1;
        mask = &mask_1;
    }
    else {
        port = I8259_PORT_2;
        mask = &mask_2;
        irq -= 8;
    }

    *mask |= (1 << irq);

    outb(port + 1, *mask);
}

void i8259_unmask(uint8_t irq)
{
    uint16_t port;
    uint8_t *mask;
    if(irq < 8) {
        port = I8259_PORT_1;
        mask = &mask_1;
    }
    else {
        port = I8259_PORT_2;
        mask = &mask_2;
        irq -= 8;
    }

    *mask &= ~(1 << irq);
    
    outb(port + 1, *mask);
}

void i8259_eoi(uint8_t irq)
{
    if(irq >= 8)
        outb(I8259_PORT_2, 0x20);
    outb(I8259_PORT_1, 0x20);
}
