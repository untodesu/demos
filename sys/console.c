/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:53:46 */
#include <sys/console.h>
#include <sys/kp.h>

static struct console *active_con = NULL;
static struct console *clist_tail = NULL;

void console_reg(struct console *console)
{
    struct console *it;
    for(it = clist_tail; it; it = it->next) {
        if(it == console) {
            kp_warn("console: %s is already registered", console->name);
            return;
        }
    }

    if(console->flags & CON_FLUSH_INIT)
        kp_flush(console);
    if(console->flags & CON_AUTO_ENABLE)
        active_con = console;

    console->next = clist_tail;
    clist_tail = console;
}

void console_enable(struct console *console)
{
    if(!console || console == active_con)
        return;
    active_con = console;
}

void console_disable(struct console *console)
{
    if(!console || console != active_con)
        return;
    active_con = NULL;
}

void console_write(const void *s, size_t n)
{
    if(!active_con || !active_con->write_fn)
        return;
    active_con->write_fn(active_con, s, n);
}
