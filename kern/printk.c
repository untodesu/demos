/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/printk.h>
#include <sys/sprintf.h>
#include <sys/string.h>

typedef char printk_msg_t[CONFIG_PRINTK_MESSAGE_SIZE];

static printk_msg_t printk_buf[CONFIG_PRINTK_BUFFER_LENGTH] = { 0 };
static size_t printk_buf_beg = 0;
static size_t printk_buf_end = 0;

struct console *console_drivers = NULL;
short log_level = 20;

static void call_console_drivers(const void *s, size_t n)
{
    struct console *con;
    for(con = console_drivers; con; con = con->next) {
        if(!con->write)
            continue;
        con->write(con, s, n);
    }
}

int printkv(int level, const char *fmt, va_list va)
{
    int result;
    printk_msg_t *msg;

    if(level < log_level) {
        msg = printk_buf + printk_buf_end;

        memset(*msg, 0, sizeof(printk_msg_t));
        result = vsnprintf(*msg, sizeof(printk_msg_t) - 2, fmt, va);
        strncat(*msg, "\r\n", sizeof(printk_msg_t));
        call_console_drivers(*msg, strlen(*msg));

        printk_buf_end++;
        printk_buf_beg = printk_buf_end / CONFIG_PRINTK_BUFFER_LENGTH;
        printk_buf_end = printk_buf_end % CONFIG_PRINTK_BUFFER_LENGTH;

        return result;
    }

    return 0;
}

int printk(int level, const char *fmt, ...)
{
    va_list va;
    int result;

    if(level < log_level) {
        va_start(va, fmt);
        result = printkv(level, fmt, va);
        va_end(va);

        return result;
    }

    return 0;
}

void register_console(struct console *newcon)
{
    printk_msg_t *msg;
    unsigned int i;

    if(newcon->write) {
        for(i = 0; i < CONFIG_PRINTK_BUFFER_LENGTH; i++) {
            msg = printk_buf + (i + printk_buf_end) % CONFIG_PRINTK_BUFFER_LENGTH;
            newcon->write(newcon, *msg, strlen(*msg));
        }
    }

    newcon->index = console_drivers ? (console_drivers->index + 1) : 0;
    newcon->next = console_drivers;

    console_drivers = newcon;
}
