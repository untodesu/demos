/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/console.h>
#include <sys/printk.h>

struct console *console_drivers = NULL;

void register_console(struct console *console)
{
    struct console *console_it;

    for(console_it = console_drivers; console_it; console_it = console_it->next) {
        if(console_it == console) {
            pk_warn("console: %s [%hd] is already registered", console_it->name, console_it->index);
            return;
        }
    }

    if(console->flags & CONSOLE_FLUSH_ON_INIT) {
        /* We only operate with registering
         * and unregistering consoles here,
         * printing is actually managed by
         * printk; so we call it here... */
        printk_flush_console(console);
    }

    console->index = console_drivers ? (console_drivers->index + 1) : 0;
    console->next = console_drivers;
    console_drivers = console;
}

int unregister_console(struct console *console)
{
    struct console *acon, *bcon;

    if(console_drivers == console) {
        console_drivers = console->next;
        return 1;
    }

    if(console_drivers) {
        for(acon = console_drivers->next, bcon = console_drivers; acon; bcon = acon, acon = bcon->next) {
            if(acon == console) {
                bcon->next = acon->next;
                return 1;
            }
        }
    }

    return 0;
}
