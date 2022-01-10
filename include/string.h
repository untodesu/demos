/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _STRING_H_
#define _STRING_H_ 1
#include <stddef.h>

/* Please notice that some of functions with
 * size-limiting argument directly violate the
 * standard definition of such functions in order
 * to make the code a safer place.
 * So when you use strncat, the third argument actually
 * is the total  size of destination buffer rather than
 * a maximum string size to concatenate. */

const void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);
const char *strchr(const char *s, int c);
const char *strrchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
int strcasecmp(const char *s1, const char *s2);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
char *strncat(char *s1, const char *s2, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strncpy(char *s1, const char *s2, size_t n);

#endif
