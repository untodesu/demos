/* SPDX-License-Identifier: BSD-2-Clause */
#include <config.h>
#include <sys/klog.h>
#include <sys/ksprintf.h>
#include <sys/kstring.h>

/* klog your toilet */

struct klog_message {
    int level;
    char message[CONFIG_KLOG_ENTRY_SIZE];
};

static int klog_level = KLOG_DBG;
static unsigned int klog_begin = 0;
static unsigned int klog_end = 0;
static struct klog_message klog_buf[CONFIG_KLOG_ENTRY_COUNT] = { 0 };
static klog_sink_t klog_sink = NULL;

static const char *klog_get_prefix(int level)
{
    static char str[32] = { 0 };
    unsigned int color;
    const char *prefix;
    switch(level) {
        case KLOG_INF:
            color = 36;
            prefix = "INF";
            break;
        case KLOG_WRN:
            color = 33;
            prefix = "WRN";
            break;
        case KLOG_ERR:
            color = 31;
            prefix = "ERR";
            break;
        case KLOG_FTL:
            color = 31;
            prefix = "FTL";
            break;
        case KLOG_DBG:
            color = 37;
            prefix = "DBG";
            break;
        default:
            color = 35;
            prefix = "???";
            break;
    }
    snprintf(str, sizeof(str), "\033[1;%um[%3s]\033[0m ", color, prefix);
    return str;
}

static void klog_print(const struct klog_message *msg)
{
    int nc;
    static char print_buffer[2048] = { 0 };
    if(!klog_sink || msg->level < klog_level || !msg->message[0])
        return;
    if((nc = snprintf(print_buffer, sizeof(print_buffer), "%s%s\r\n", klog_get_prefix(msg->level), msg->message)) <= 0)
        return;
    klog_sink(print_buffer, nc);
}

static void klog_push(const struct klog_message *msg)
{
    memcpy(klog_buf + klog_end, msg, sizeof(struct klog_message));
    klog_print(klog_buf + klog_end);

    klog_end++;
    klog_begin = klog_end / CONFIG_KLOG_ENTRY_COUNT;
    klog_end = klog_end % CONFIG_KLOG_ENTRY_COUNT;
}

void init_klog(void)
{
    memset(klog_buf, 0, sizeof(klog_buf));
    klog_begin = 0;
    klog_end = 0;
}

void set_klog_sink(klog_sink_t sink)
{
    unsigned int i;
    if((klog_sink = sink)) {
        for(i = 0; i < CONFIG_KLOG_ENTRY_COUNT; i++)
            klog_print(klog_buf + (i + klog_end) % CONFIG_KLOG_ENTRY_COUNT);
    }
}

void set_klog_level(int level)
{
    klog_level = level;
}

void klogv(int level, const char *fmt, va_list va)
{
    struct klog_message msg = { .level = level };
    vsnprintf(msg.message, sizeof(msg.message), fmt, va);
    klog_push(&msg);
}

void klog(int level, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    klogv(level, fmt, va);
    va_end(va);
}
