/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 22:12:40 */
#include <ksprintf.h>
#include <string.h>
#include <sys/console.h>
#include <sys/kp.h>

short kp_level = 20;
static char kp_buffer[KP_BUFSIZE] = { 0 };
static size_t kp_writepos = 0;

size_t kprintf(short level, const char *fmt, ...)
{
    size_t r;
    va_list va;

    if(level < kp_level) {
        va_start(va, fmt);
        r = kvprintf(level, fmt, va);
        va_end(va);
        return r;
    }

    return 0;
}

size_t kvprintf(short level, const char *fmt, va_list va)
{
    size_t r, i, n;
    char buf[1024] = { 0 };

    if(level < kp_level) {
        r = kvsnprintf(buf, sizeof(buf) - 3, fmt, va);
        kstrncat(buf, "\r\n", sizeof(buf));
        console_write(buf, n = strlen(buf));
        for(i = 0; i < n; i++) {
            kp_buffer[kp_writepos++] = buf[i];
            kp_writepos %= KP_BUFSIZE;
        }

        return r;
    }

    return 0;
}

void kp_flush(struct console *console)
{
    if(console && console->write_fn) {
        console->write_fn(console, kp_buffer + kp_writepos, KP_BUFSIZE - kp_writepos);
        console->write_fn(console, kp_buffer, kp_writepos);
    }
}
