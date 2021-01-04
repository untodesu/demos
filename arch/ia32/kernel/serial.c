#include <arch/io.h>
#include <arch/serial.h>

#define NUM_PORTS 4

struct serial_port {
    uint16_t io;
    int ok;
};

static struct serial_port ports[NUM_PORTS] = {
    { .io = 0x3F8, .ok = 0 },
    { .io = 0x2F8, .ok = 0 },
    { .io = 0x3E8, .ok = 0 },
    { .io = 0x2E8, .ok = 0 },
};

int serial_init(int id, unsigned int speed)
{
    if(id < 0 || id >= NUM_PORTS)
        return 0;

    struct serial_port *port = ports + id;

    uint16_t divisor = (uint16_t)(speed ? (115200 / speed) : 0);

    outb(port->io + 1, 0x00);
    outb(port->io + 3, 0x80);
    outb(port->io + 0, (divisor & 0x00FF));
    outb(port->io + 1, (divisor & 0xFF00) >> 8);
    outb(port->io + 3, 0x03);
    outb(port->io + 2, 0xC7);
    outb(port->io + 4, 0x0B);

    outb(port->io + 4, 0x1E);
    outb(port->io + 0, 0xAE);
    if(inb(port->io + 0) != 0xAE) {
        port->ok = 0;
        return 0;
    }

    outb(port->io + 4, 0x0F);
    port->ok = 1;
    return 1;
}

void serial_write(int id, const void *s, size_t n)
{
    if(id < 0 || id >= NUM_PORTS)
        return;

    struct serial_port *port = (ports + id);
    if(!port->ok)
        return;

    const unsigned char *sp = s;
    while(n--) {
        if(*sp == '\n') {
            while((inb(port->io + 5) & 0x20) == 0);
            outb(port->io, '\r');
        }

        while((inb(port->io + 5) & 0x20) == 0);
        outb(port->io, *sp++);
    }
}
