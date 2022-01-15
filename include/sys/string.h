/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _SYS_STRING_H_
#define _SYS_STRING_H_ 1
#include <stddef.h>

char *strncat(char *s1, const char *s2, size_t n);
char *strncpy(char *s1, const char *s2, size_t n);
const char *strchr(const char *s, int c);
const char *strrchr(const char *s, int c);
const void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
void *memcpy(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);

#endif
