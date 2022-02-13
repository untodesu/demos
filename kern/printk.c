/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/printk.h>
#include <sys/sprintf.h>
#include <sys/string.h>

typedef char pk_msg_t[CONFIG_PK_MSG_SIZE];

static pk_msg_t pk_buffer[CONFIG_PK_BUFFER_LENGTH] = { 0 };
static size_t pk_buffer_beg = 0;
static size_t pk_buffer_end = 0;
static short pk_log_level = 20;

struct pk_sink *pk_sinks = NULL;

static void pk_write_all(const void *s, size_t n)
{
    struct pk_sink *sink;
    for(sink = pk_sinks; sink; sink = sink->next) {
        if(!sink->write)
            continue;
        sink->write(sink, s, n);
    }
}

int printkv(int level, const char *fmt, va_list va)
{
    int result;
    pk_msg_t *msg;

    if(level < pk_log_level) {
        msg = pk_buffer + pk_buffer_end;

        memset(*msg, 0, sizeof(pk_msg_t));
        result = vsnprintf(*msg, sizeof(pk_msg_t) - 3, fmt, va);
        strncat(*msg, "\r\n", sizeof(pk_msg_t));
        pk_write_all(*msg, strlen(*msg));

        pk_buffer_end++;
        pk_buffer_beg = pk_buffer_end / CONFIG_PK_BUFFER_LENGTH;
        pk_buffer_end = pk_buffer_end % CONFIG_PK_BUFFER_LENGTH;

        return result;
    }

    return 0;
}

int printk(int level, const char *fmt, ...)
{
    int result;
    va_list va;

    if(level < pk_log_level) {
        va_start(va, fmt);
        result = printkv(level, fmt, va);
        va_end(va);
        return result;
    }

    return 0;
}

void set_pk_level(short new_level)
{
    pk_log_level = new_level;
}

void register_pk_sink(struct pk_sink *sink)
{
    unsigned int i;
    pk_msg_t *msg;

    if(sink->write) {
        for(i = 0; i < CONFIG_PK_BUFFER_LENGTH; i++) {
            msg = pk_buffer + (i + pk_buffer_end) % CONFIG_PK_BUFFER_LENGTH;
            sink->write(sink, *msg, strlen(*msg));
        }
    }

    sink->index = pk_sinks ? (pk_sinks->index + 1) : 0;
    sink->next = pk_sinks;

    pk_sinks = sink;
}
