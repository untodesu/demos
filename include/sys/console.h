/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_CONSOLE_H_
#define _SYS_CONSOLE_H_ 1
#include <stddef.h>

#define CONSOLE_MAX_NAME 32
#define CONSOLE_NULL_INDEX (-1)
#define CONSOLE_FLUSH_ON_INIT (1 << 0)

struct console;
typedef void(*console_write_t)(struct console *, const void *, size_t);

struct console {
    char name[32];
    short flags;
    short index;
    void *data;
    console_write_t write;
    struct console *next;
};

extern struct console *console_drivers;

void register_console(struct console *console);
int unregister_console(struct console *console);

#endif
