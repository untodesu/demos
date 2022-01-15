/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/ctype.h>
#include <sys/string.h>

char *strncat(char *s1, const char *s2, size_t n)
{
    size_t nc;
    char *save = s1;
    while(*s1 && n--)
        s1++;
    nc = strnlen(s2, --n);
    s1[nc] = 0;
    memcpy(s1, s2, nc);
    return save;
}

char *strncpy(char *s1, const char *s2, size_t n)
{
    char *save = s1;
    while(*s2 && n--)
        *s1++ = *s2++;
    if(n)
        *s1 = 0;
    return save;
}

const char *strchr(const char *s, int c)
{
    while(*s) {
        if(*s == c)
            return s;
        s++;
    }
    return NULL;
}

const char *strrchr(const char *s, int c)
{
    const char *cp = NULL;
    do {
        if(*s == c)
            cp = s;
    } while(*s++);
    return cp;
}

const void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *sp = s;
    while(n--) {
        if(*sp == c)
            return sp;
        sp++;
    }
    return NULL;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *sp1 = s1;
    const unsigned char *sp2 = s2;
    while(n--) {
        if(*sp1 != *sp2)
            return *sp1 - *sp2;
        sp1++;
        sp2++;
    }
    return 0;
}

int strcmp(const char *s1, const char *s2)
{
    while(*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    while(*s1 && *s1 == *s2 && n--) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

size_t strlen(const char *s)
{
    size_t i;
    for(i = 0; *s++; i++);
    return i;
}

size_t strnlen(const char *s, size_t n)
{
    size_t i;
    for(i = 0; *s++ && i < n; i++);
    return i;
}

void *memcpy(void *s1, const void *s2, size_t n)
{
    unsigned char *sp1 = s1;
    const unsigned char *sp2 = s2;
    while(n--)
        *sp1++ = *sp2++;
    return s1;
}

void *memset(void *s, int c, size_t n)
{
    unsigned char *sp = s;
    while(n--)
        *sp++ = (unsigned char)c;
    return s;
}
