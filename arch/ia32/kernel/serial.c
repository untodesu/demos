#include <arch/io.h>
#include <arch/serial.h>
#include <demos/config.h>

#define PORT 0x3F8

int serial_init(void)
{
    // todo: use a divisors array to void nasty
    // division even though it is fast enough.
    uint16_t divisor = 115200 / CONFIG_SERIAL_RATE;
    if(divisor == 0)
        divisor = 1;

    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, (divisor & 0x00FF));
    outb(PORT + 1, (divisor & 0xFF00) >> 8);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x0B);

    outb(PORT + 4, 0x1E);
    outb(PORT + 0, 0xAE);
    if(inb(PORT + 0) != 0xAE)
        return 0;

    outb(PORT + 4, 0x0F);
    return 1;
}

void serial_write(const void *s, size_t n)
{
    const unsigned char *sp = s;
    while(n--) {
        if(*sp == '\n') {
            while((inb(PORT + 5) & 0x20) == 0);
            outb(PORT, '\r');
        }
        
        while((inb(PORT + 5) & 0x20) == 0);
        outb(PORT, *sp++);
    }
}
