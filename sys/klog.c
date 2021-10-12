#include <lib/sprintf.h>
#include <lib/string.h>
#include <sys/config.h>
#include <sys/klog.h>

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

static inline int get_level_char(int level)
{
    switch(level) {
        case KLOG_INFO:
            return 'I';
        case KLOG_WARN:
            return 'W';
        case KLOG_ERROR:
            return 'E';
        case KLOG_FATAL:
            return '!';
        case KLOG_DEBUG:
            return 'D';
        default:
            return '?';
    }        
}

static void klog_print(const struct klog_message *msg)
{
    int nc;
    static char print_buffer[2048] = { 0 };
    if(!klog_print_func || msg->level < klog_level || !msg->message[0])
        return;
    if((nc = snprintf(print_buffer, sizeof(print_buffer), "[%c] %s\n", get_level_char(msg->level), msg->message)) <= 0)
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
