#include <lib/sprintf.h>
#include <lib/string.h>
#include <sys/kprintf.h>

static char kprintf_buffer[1024] = { 0 };
static kprintf_func_t kprintf_func = NULL;

void set_kprintf_func(kprintf_func_t func)
{
    kprintf_func = func;
}

void kprintf(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    kvprintf(fmt, va);
    va_end(va);
}

void kvprintf(const char *fmt, va_list va)
{
    int nc;
    if(kprintf_func) {
        if((nc = vsnprintf(kprintf_buffer, sizeof(kprintf_buffer), fmt, va)) <= 0)
            return;
        if((size_t)nc >= sizeof(kprintf_buffer) - 2)
            nc = sizeof(kprintf_buffer) - 2;
        kprintf_buffer[++nc] = '\n';
        kprintf_buffer[++nc] = '\0';
        kprintf_func(kprintf_buffer, nc);
    }
}
