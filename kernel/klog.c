#include <config.h>
#include <demos/klog.h>
#include <sprintf.h>
#include <string.h>

#define KLOG_MESSAGE_SIZE 1024

struct klog_message {
    int level;
    char message[KLOG_MESSAGE_SIZE];
};

static int klog_level = KLOG_DEBUG;
static unsigned int klog_begin = 0;
static unsigned int klog_end = 0;
static struct klog_message klog_buf[KLOG_BUFFER_SIZE] = { 0 };
static klog_print_func_t klog_print_func = NULL;

static const char *klog_get_prefix(int level)
{
    static char str[32] = { 0 };
    unsigned int color;
    const char *prefix;
    switch(level) {
        case KLOG_INFO:
            color = 92;
            prefix = "INF";
            break;
        case KLOG_WARN:
            color = 93;
            prefix = "WRN";
            break;
        case KLOG_ERROR:
            color = 91;
            prefix = "ERR";
            break;
        case KLOG_FATAL:
            color = 91;
            prefix = "FTL";
            break;
        case KLOG_DEBUG:
            color = 37;
            prefix = "DBG";
            break;
        default:
            color = 95;
            prefix = "???";
            break;
    }
    snprintf(str, sizeof(str), "\033[%um[%3s]\033[0m ", color, prefix);
    return str;
}

static void klog_print(const struct klog_message *msg)
{
    int nc;
    static char print_buffer[2048] = { 0 };
    if(!klog_print_func || msg->level < klog_level || !msg->message[0])
        return;
    if((nc = snprintf(print_buffer, sizeof(print_buffer), "%s%s\r\n", klog_get_prefix(msg->level), msg->message)) <= 0)
        return;
    klog_print_func(print_buffer, nc);
}

static void klog_push(const struct klog_message *msg)
{
    memcpy(klog_buf + klog_end, msg, sizeof(struct klog_message));
    klog_print(klog_buf + klog_end);

    klog_end++;
    klog_begin = klog_end / KLOG_BUFFER_SIZE;
    klog_end = klog_end % KLOG_BUFFER_SIZE;
}

void init_klog(void)
{
    memset(klog_buf, 0, sizeof(klog_buf));
    klog_begin = 0;
    klog_end = 0;
}

void set_klog_print_func(klog_print_func_t func)
{
    unsigned int i;
    if((klog_print_func = func)) {
        for(i = 0; i < KLOG_BUFFER_SIZE; i++)
            klog_print(klog_buf + (i + klog_end) % KLOG_BUFFER_SIZE);
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
