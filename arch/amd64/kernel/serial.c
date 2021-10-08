#include <arch/io.h>
#include <arch/serial.h>

static uint16_t get_port(int id)
{
    switch(id) {
        case SERIAL0:
            return 0x03F8;
        case SERIAL1:
            return 0x02F8;
        case SERIAL2:
            return 0x03E8;
        case SERIAL3:
            return 0x02E8;
        default:
            return 0xFFFF;
    }
}

int init_serial(int id, unsigned int rate)
{
    uint16_t div = rate ? (115200 / rate) : 1;
    uint16_t port = get_port(id);
    if(port == 0xFFFF)
        return 0;

    outb(port + 1, 0x00);
    outb(port + 3, 0x80);
    outb(port + 0, div & 0xFF);
    outb(port + 1, (div >> 8) & 0xFF);
    outb(port + 3, 0x03);
    outb(port + 2, 0xC7);
    outb(port + 4, 0x0B);

    outb(port + 4, 0x1E);
    outb(port + 0, 0x42);
    if(inb(port + 0) != 0x42)
        return 0;
    outb(port + 4, 0x0F);

    return 1;
}

void serial_write(int id, const void *s, size_t n)
{
    uint16_t port = get_port(id);
    if(port != 0xFFFF) {
        const unsigned char *sp = s;
        while(n--) {
            while(!(inb(port + 5) & 0x20));
            outb(port + 0, *sp++);
        }
    }
}
