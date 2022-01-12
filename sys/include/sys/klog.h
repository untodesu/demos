/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_KLOG_H_
#define _SYS_KLOG_H_ 1
#include <sys/cdefs.h>
#include <stdarg.h>
#include <stddef.h>

enum {
    KLOG_INF = 1,
    KLOG_WRN = 2,
    KLOG_ERR = 3,
    KLOG_FTL = 9,
    KLOG_DBG = 0
};

typedef void(*klog_sink_t)(const void *, size_t);

void set_klog_sink(klog_sink_t sink);
void set_klog_level(int level);
void klogv(int level, const char *fmt, va_list va);
void klog(int level, const char *fmt, ...);

#endif
