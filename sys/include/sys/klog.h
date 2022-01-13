/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_KLOG_H_
#define _SYS_KLOG_H_ 1
#include <sys/cdefs.h>
#include <sys/initcall.h>
#include <stdarg.h>
#include <stddef.h>

#define KLOG_INFO   1
#define KLOG_WARN   2
#define KLOG_ERROR  3
#define KLOG_FATAL  9
#define KLOG_DEBUG  0

typedef void(*klog_sink_t)(const void *, size_t);

void set_klog_sink(klog_sink_t sink);
void set_klog_level(int level);
void klogv(int level, const char *fmt, va_list va);
void klog(int level, const char *fmt, ...);

initcall_extr(klog);

#endif
