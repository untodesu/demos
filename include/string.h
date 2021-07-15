#ifndef STRING_H
#define STRING_H 1
#include <arch/stddef.h>

void *memset(void *s, int c, size_t n);
void *memcpy(void *a, const void *b, size_t n);
int memcmp(const void *a, const void *b, size_t n);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
char *strcpy(char *a, const char *b);
char *strncpy(char *a, const char *b, size_t n);
int strcmp(const char *a, const char *b);
int stricmp(const char *a, const char *b);
const char *strchr(const char *s, char c);
const char *strrchr(const char *s, char c);

#endif
