#ifndef __DEMOS_STRING_H__
#define __DEMOS_STRING_H__ 1
#include <arch/types.h>

void * memset(void *s, int c, size_t n);
void * memcpy(void *s1, const void *s2, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
char * strcpy(char *s1, const char *s2);
char * strncpy(char *s1, const char *s2, size_t n);
int strcmp(const char *s1, const char *s2);
int stricmp(const char *s1, const char *s2);
const char * strchr(const char *s, char c);
const char * strrchr(const char *s, char c);

#endif
