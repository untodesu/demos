/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/initcall.h>
#include <sys/intr.h>
#include <sys/io.h>
#include <sys/printk.h>
#include <sys/string.h>

#define UART_CLOCK 115200

#define UART_THB 0  /* (WO) Transmitter Holding Buffer          */
#define UART_RBR 0  /* (RO) Receiver Buffer                     */
#define UART_DLL 0  /* (RW) Divisor Latch Low Byte              */
#define UART_DLH 1  /* (RW) Divisor Latch High Byte             */
#define UART_IER 1  /* (RW) Interrupt Enable Register           */
#define UART_IIR 2  /* (RO) Interrupt Identification Register   */
#define UART_FCR 2  /* (WO) FIFO Control Register               */
#define UART_LCR 3  /* (RW) Line Control Register               */
#define UART_MCR 4  /* (RW) Modem Control Register              */
#define UART_LSR 5  /* (RO) Line Status Register                */
#define UART_MSR 6  /* (RO) Modem Status Register               */
#define UART_SCR 7  /* (RW) Scratch Register                    */

struct ns16550_state {
    char name[16];
    io_addr_t base;
    unsigned int speed;
};

static int init_ns16550(struct ns16550_state *ns)
{
    unsigned int divisor;

    /* Check for presense */
    io_write8(ns->base + UART_SCR, 0xAE);
    if(io_read8(ns->base + UART_SCR) != 0xAE) {
        pk_notice("ns16550: %s not present", ns->name);
        return 0;
    }

    divisor = ns->speed ? (UART_CLOCK / ns->speed) : 1;

    /* Initialize */
    io_write8(ns->base + UART_IER, 0x00);
    io_write8(ns->base + UART_LCR, 0x80);
    io_write8(ns->base + UART_DLL, (divisor & 0x00FF));
    io_write8(ns->base + UART_DLH, (divisor & 0xFF00) >> 8);
    io_write8(ns->base + UART_LCR, 0x03);
    io_write8(ns->base + UART_FCR, 0xC7);
    io_write8(ns->base + UART_MCR, 0x0B);

    /* Check */
    io_write8(ns->base + UART_MCR, 0x1E);
    io_write8(ns->base + UART_THB, 0xAE);
    if(io_read8(ns->base + UART_RBR) != 0xAE) {
        pk_warn("ns16550: %s is faulty", ns->name);
        return 0;
    }

    io_write8(ns->base + UART_MCR, 0x0F);

    return 1;
}

static void ns16550_write(struct ns16550_state *ns, const void *s, size_t n)
{
    const io_uint8_t *sp = s;
    while(n--) {
        while(!(io_read8(ns->base + UART_LSR) & 0x20));
        io_write8(ns->base + UART_THB, *sp++);
    }
}

#define NUM_PORTS 2

static struct pk_sink port_sinks[NUM_PORTS] = { 0 };
static struct ns16550_state ports[NUM_PORTS] = {
    [0] = {
        .name = "ttyS0",
        .base = 0x3F8,
        .speed = CONFIG_NS16550_DEFAULT_SPEED
    },
    [1] = {
        .name = "ttyS1",
        .base = 0x2F8,
        .speed = CONFIG_NS16550_DEFAULT_SPEED
    }
};

static void ns16550_sink_write(struct pk_sink *sink, const void *s, size_t n)
{
    ns16550_write(sink->sink_data, s, n);
}

static int init_ns16550_console(void)
{
    unsigned int i;
    for(i = 0; i < NUM_PORTS; i++) {
        if(init_ns16550(&ports[i])) {
            memset(port_sinks[i].name, 0, sizeof(port_sinks[i].name));
            strncpy(port_sinks[i].name, ports[i].name, sizeof(port_sinks[i].name));
            port_sinks[i].write = &ns16550_sink_write;
            port_sinks[i].sink_data = &ports[i];
            port_sinks[i].index = PK_INVALID_INDEX;
            register_pk_sink(&port_sinks[i]);
        }
    }

    return 0;
}
kernel_initcall(ns16550_console, init_ns16550_console);
