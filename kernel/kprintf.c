#include <demos/kprintf.h>
#include <sprintf.h>

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
    if(kprintf_func) {
        int nc = vsnprintf(kprintf_buffer, sizeof(kprintf_buffer), fmt, va);
        if(nc > 0)
            kprintf_func(kprintf_buffer, (size_t)nc);
    }
}
