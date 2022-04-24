/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:14:52 */
#ifndef _STRING_H_
#define _STRING_H_ 1
#include <stddef.h>

const void *memchr(const void *s, int c, size_t n);
int memcmp(const void *sa, const void *sb, size_t n);
void *memcpy(void *sd, const void *ss, size_t n);
void *memset(void *s, int c, size_t n);

char *strcat(char *sd, const char *ss);
const char *strchr(const char *s, int c);
int strcmp(const char *sa, const char *sb);
char *strcpy(char *sd, const char *ss);
size_t strlen(const char *s);
char *strncat(char *sd, const char *ss, size_t n);
int strncmp(const char *sa, const char *sb, size_t n);
char *strncpy(char *sd, const char *ss, size_t n);
size_t strnlen(const char *s, size_t n);
const char *strrchr(const char *s, int c);
const char *strstr(const char *sa, const char *sb);

/* These have altered behaviour: the size_t
 * argument in them is used as a size value
 * of the destination buffer, not source. */
char *kstrncat(char *sd, const char *ss, size_t n);
char *kstrncpy(char *sd, const char *ss, size_t n);

#if 0 /* ToDo */
const char *strerror(int errno);
const char *strsignal(int sig);
#endif

#endif
