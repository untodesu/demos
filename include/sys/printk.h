/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_PRINTK_H_
#define _SYS_PRINTK_H_ 1
#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

#define LOGLEVEL_EMERG  0
#define LOGLEVEL_ALERT  1
#define LOGLEVEL_CRIT   2
#define LOGLEVEL_ERROR  3
#define LOGLEVEL_WARN   4
#define LOGLEVEL_NOTICE 5
#define LOGLEVEL_INFO   6
#define LOGLEVEL_DEBUG  7

#define CON_INDEX_INIT -1

struct console {
    char name[32];
    void(*write)(struct console *, const void *, size_t);
    void *driver_data;
    short index;
    struct console *next;
};

extern struct console *console_drivers;
extern short log_level;

int printkv(int level, const char *fmt, va_list va);
int printk(int level, const char *fmt, ...) __format(printf, 2, 3);
void register_console(struct console *newcon);

#endif
