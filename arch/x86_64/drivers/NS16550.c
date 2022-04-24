/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sun Apr 24 2022 17:31:52 */
#include <sys/console.h>
#include <sys/initcall.h>
#include <sys/io.h>
#include <sys/kp.h>

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

struct NS16550 {
    io_addr_t base;
    unsigned int speed;
};

static int setup_NS16550(struct NS16550 *ns)
{
    unsigned int divisor;

    /* Check for presense */
    io_write8(ns->base + UART_SCR, 0xAE);
    if(io_read8(ns->base + UART_SCR) != 0xAE) {
        kp_notice("ns16550: 0x%04X is not present", ns->base);
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
        kp_warn("ns16550: 0x%04X is faulty", ns->base);
        return 0;
    }

    io_write8(ns->base + UART_MCR, 0x0F);

    kp_debug("ns16550: 0x%04X is OK", ns->base);
    return 1;
}

static void NS16550_write(struct NS16550 *ns, const void *s, size_t n)
{
    const io_uint8_t *sp = s;
    while(n--) {
        while(!(io_read8(ns->base + UART_LSR) & 0x20));
        io_write8(ns->base + UART_THB, *sp++);
    }
}

static size_t NS16550_console_write(struct console *console, const void *s, size_t n)
{
    NS16550_write(console->data, s, n);
    return n;
}

static struct NS16550 ns_serial0 = {
    .base = 0x03F8,
    .speed = 9600
};

static struct console console_serial0 = {
    .name = "ttyS0",
    .init_fn = NULL,
    .write_fn = &NS16550_console_write,
    .flags = CON_FLUSH_INIT | CON_AUTO_ENABLE,
    .data = &ns_serial0,
    .next = NULL
};

static int init_NS16550(void)
{
    if(!setup_NS16550(&ns_serial0))
        return 1;
    console_reg(&console_serial0);
    return 0;
}
initcall_tier_0(NS16550, init_NS16550);
