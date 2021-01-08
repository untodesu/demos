#include <arch/i8259.h>
#include <arch/io.h>

#define PIC1_PORT 0x20
#define PIC2_PORT 0xA0

static uint8_t pic1_mask = 0xFF & ~(1 << 2);
static uint8_t pic2_mask = 0xFF;

void init_pic(void)
{
    outb(PIC1_PORT + 0, 0x11);
    outb(PIC2_PORT + 0, 0x11);
    outb(PIC1_PORT + 1, PIC_IRQ0);
    outb(PIC2_PORT + 1, PIC_IRQ8);
    outb(PIC1_PORT + 1, 0x04);
    outb(PIC2_PORT + 1, 0x02);
    outb(PIC1_PORT + 1, 0x01);
    outb(PIC2_PORT + 1, 0x01);
    outb(PIC1_PORT + 1, pic1_mask);
    outb(PIC2_PORT + 1, pic2_mask);
}

void pic_mask_irq(uint8_t irq_no)
{
    uint16_t port;
    uint8_t *mask;
    if(irq_no < 8) {
        port = PIC1_PORT;
        mask = &pic1_mask;
    }
    else {
        port = PIC2_PORT;
        mask = &pic2_mask;
        irq_no -= 8;
    }

    *mask |= (1 << irq_no);
    outb(port + 1, *mask);
}

void pic_unmask_irq(uint8_t irq_no)
{
    uint16_t port;
    uint8_t *mask;
    if(irq_no < 8) {
        port = PIC1_PORT;
        mask = &pic1_mask;
    }
    else {
        port = PIC2_PORT;
        mask = &pic2_mask;
        irq_no -= 8;
    }

    *mask &= ~(1 << irq_no);
    outb(port + 1, *mask);
}

void pic_send_eoi(uint8_t irq_no)
{
    if(irq_no >= 8)
        outb(PIC2_PORT, 0x20);
    outb(PIC1_PORT, 0x20);
}
