/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 22:04:09 */
#ifndef _SYS_KP_H_
#define _SYS_KP_H_ 1
#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

#define KP_BUFSIZE 8192

#define KPL_EMERG   0
#define KPL_ALERT   1
#define KPL_CRIT    2
#define KPL_ERROR   3
#define KPL_WARN    4
#define KPL_NOTICE  5
#define KPL_INFORM  6
#define KPL_DEBUG   7

extern short kp_level;

size_t kprintf(short level, const char *fmt, ...) __format(printf, 2, 3);
size_t kvprintf(short level, const char *fmt, va_list va);

struct console;
void kp_flush(struct console *console);

#define kp_emerg(fmt, ...)  kprintf(KPL_EMERG,  (fmt), ##__VA_ARGS__)
#define kp_alert(fmt, ...)  kprintf(KPL_ALERT,  (fmt), ##__VA_ARGS__)
#define kp_crit(fmt, ...)   kprintf(KPL_CRIT,   (fmt), ##__VA_ARGS__)
#define kp_error(fmt, ...)  kprintf(KPL_ERROR,  (fmt), ##__VA_ARGS__)
#define kp_warn(fmt, ...)   kprintf(KPL_WARN,   (fmt), ##__VA_ARGS__)
#define kp_notice(fmt, ...) kprintf(KPL_NOTICE, (fmt), ##__VA_ARGS__)
#define kp_inform(fmt, ...) kprintf(KPL_INFORM, (fmt), ##__VA_ARGS__)
#define kp_debug(fmt, ...)  kprintf(KPL_DEBUG,  (fmt), ##__VA_ARGS__)

#endif
