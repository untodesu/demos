#ifndef __SYS_KLOG_H__
#define __SYS_KLOG_H__ 1
#include <lib/compiler.h>
#include <lib/stdarg.h>
#include <lib/stddef.h>

#define KLOG_INFO   1
#define KLOG_WARN   2
#define KLOG_ERROR  3
#define KLOG_FATAL  64
#define KLOG_DEBUG  0

typedef void(*klog_print_func_t)(const void *, size_t);

void init_klog(void);
void set_klog_print_func(klog_print_func_t func);
void set_klog_level(int level);
void klogv(int level, const char *fmt, va_list va);
void klog(int level, const char *fmt, ...) __printf(2, 3);

#endif
