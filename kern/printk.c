/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/console.h>
#include <sys/printk.h>
#include <sys/sprintf.h>
#include <sys/string.h>

typedef char printk_msg_t[CONFIG_PRINTK_MSG_SIZE];

static printk_msg_t printk_buffer[CONFIG_PRINTK_BUFFER_LENGTH] = { 0 };
static size_t printk_buffer_beg = 0;
static size_t printk_buffer_end = 0;

short printk_level = 20;

static void write_to_consoles(const void *s, size_t n)
{
    struct console *console;
    for(console = console_drivers; console; console = console->next) {
        if(!console->write)
            continue;
        console->write(console, s, n);
    }
}

int printkv(int level, const char *fmt, va_list va)
{
    int result;
    printk_msg_t *msg;

    if(level < printk_level) {
        msg = printk_buffer + printk_buffer_end;

        memset(*msg, 0, sizeof(printk_msg_t));
        result = vsnprintf(*msg, sizeof(printk_msg_t) - 3, fmt, va);
        strncat(*msg, "\r\n", sizeof(printk_msg_t));
        write_to_consoles(*msg, strlen(*msg));

        printk_buffer_end++;
        printk_buffer_beg = printk_buffer_end / CONFIG_PRINTK_BUFFER_LENGTH;
        printk_buffer_end = printk_buffer_end % CONFIG_PRINTK_BUFFER_LENGTH;

        return result;
    }

    return 0;
}

int printk(int level, const char *fmt, ...)
{
    int result;
    va_list va;

    if(level < printk_level) {
        va_start(va, fmt);
        result = printkv(level, fmt, va);
        va_end(va);
        return result;
    }

    return 0;
}

void printk_flush_console(struct console *console)
{
    unsigned int i;
    printk_msg_t *msg;

    if(console->write) {
        for(i = 0; i < CONFIG_PRINTK_BUFFER_LENGTH; i++) {
            msg = printk_buffer + (i + printk_buffer_end) % CONFIG_PRINTK_BUFFER_LENGTH;
            console->write(console, *msg, strlen(*msg));
        }
    }
}
