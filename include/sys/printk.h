/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_PRINTK_H_
#define _SYS_PRINTK_H_ 1
#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

#define PKL_EMERG   0
#define PKL_ALERT   1
#define PKL_CRIT    2
#define PKL_ERROR   3
#define PKL_WARN    4
#define PKL_NOTICE  5
#define PKL_INFO    6
#define PKL_DEBUG   7

#define PK_INVALID_INDEX (-1)

struct pk_sink {
    char name[32];
    short index;
    void *sink_data;
    void(*write)(struct pk_sink *, const void *, size_t);
    struct pk_sink *next;
};

/* access all the registered sinks */
extern struct pk_sink *pk_sinks;

int printkv(int level, const char *fmt, va_list va);
int printk(int level, const char *fmt, ...) __format(printf, 2, 3);
void set_pk_level(short new_level);
void register_pk_sink(struct pk_sink *sink);

#define pk_emerg(fmt, ...)  printk(PKL_EMERG,   (fmt), ##__VA_ARGS__)
#define pk_alert(fmt, ...)  printk(PKL_ALERT,   (fmt), ##__VA_ARGS__)
#define pk_crit(fmt, ...)   printk(PKL_CRIT,    (fmt), ##__VA_ARGS__)
#define pk_error(fmt, ...)  printk(PKL_ERROR,   (fmt), ##__VA_ARGS__)
#define pk_warn(fmt, ...)   printk(PKL_WARN,    (fmt), ##__VA_ARGS__)
#define pk_notice(fmt, ...) printk(PKL_NOTICE,  (fmt), ##__VA_ARGS__)
#define pk_info(fmt, ...)   printk(PKL_INFO,    (fmt), ##__VA_ARGS__)
#define pk_debug(fmt, ...)  printk(PKL_DEBUG,   (fmt), ##__VA_ARGS__)

#endif
