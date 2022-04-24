/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:37:23 */
#ifndef _SYS_CONSOLE_H_
#define _SYS_CONSOLE_H_ 1
#include <stddef.h>

#define CON_MAXNAME 32

#define CON_FLUSH_INIT  0x01
#define CON_AUTO_ENABLE 0x02

struct console;
typedef void(*console_init_t)(struct console *);
typedef size_t(*console_write_t)(struct console *, const void *, size_t);

struct console {
    char name[CON_MAXNAME];
    console_init_t init_fn;
    console_write_t write_fn;
    unsigned short flags;
    void *data;
    struct console *next;
};

void console_reg(struct console *console);
void console_enable(struct console *console);
void console_disable(struct console *console);
void console_write(const void *s, size_t n);

#endif
