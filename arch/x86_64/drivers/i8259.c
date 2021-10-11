#include <sys/drivers/i8259.h>
#include <sys/ports.h>

#define I8259_PORT_1 0x20
#define I8259_PORT_2 0xA0

static uint16_t mask = 0xFFFF & ~(1 << 2);

void init_i8259(void)
{
    /* ICW1 - start initializing */
    outb(I8259_PORT_1 + 0, (1 << 4) | (1 << 0));
    outb(I8259_PORT_2 + 0, (1 << 4) | (1 << 0));

    /* ICW2 - new vector offsets */
    outb(I8259_PORT_1 + 1, I8259_IRQ0);
    outb(I8259_PORT_2 + 1, I8259_IRQ8);

    /* ICW3 - chain IRQ2 to the second chip */
    outb(I8259_PORT_1 + 1, (1 << 2));
    outb(I8259_PORT_2 + 1, (1 << 1));
    
    /* ICW4 - switch to 8086/88 mode */
    outb(I8259_PORT_1 + 1, (1 << 0));
    outb(I8259_PORT_2 + 1, (1 << 0));

    /* Mask everything */
    outb(I8259_PORT_1 + 1, mask & 0xFF);
    outb(I8259_PORT_2 + 1, (mask >> 8) & 0xFF);
}

void i8259_mask(uint8_t irq_no, int set)
{
    uint16_t irq_bit = (1 << irq_no);
    uint16_t port = (irq_bit & 0xF0) ? I8259_PORT_2 : I8259_PORT_1;
    uint16_t shift = (irq_bit & 0xF0) ? 8 : 0;
    mask = set ? (mask | irq_bit) : (mask & ~irq_bit);
    outb(port + 1, (mask >> shift) & 0xFF);
}

void i8259_eoi(uint8_t irq_no)
{
    if(irq_no >= 0x08)
        outb(I8259_PORT_2, 0x20);
    outb(I8259_PORT_1, 0x20);
}

int get_i8259_irq(uint8_t int_no, uint8_t *irq_no)
{
    if(int_no >= I8259_IRQ0 && int_no <= I8259_IRQ15) {
        if(irq_no)
            *irq_no = int_no - I8259_IRQ0;
        return 1;
    }

    return 0;
}
