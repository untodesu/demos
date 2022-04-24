/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:18:10 */
#include <string.h>

const void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *sp = s;
    while(n--) {
        if(*sp == (unsigned char)c)
            return sp;
        sp++;
    }

    return NULL;
}

int memcmp(const void *sa, const void *sb, size_t n)
{
    const unsigned char *ap = sa;
    const unsigned char *bp = sb;
    while(n--) {
        if(*ap != *bp)
            return *ap - *bp;
        ap++;
        bp++;
    }

    return 0;
}

void *memcpy(void *sd, const void *ss, size_t n)
{
    unsigned char *dp = sd;
    const unsigned char *sp = ss;
    while(n--)
        *dp++ = *sp++;
    return sd;
}

void *memset(void *s, int c, size_t n)
{
    unsigned char *sp = s;
    while(n--)
        *sp++ = (unsigned char)c;
    return s;
}

char *strcat(char *sd, const char *ss)
{
    char *save = sd;
    if(*sd)
        while(*++sd);
    while((*sd++ = *ss++));
    return save;
}

const char *strchr(const char *s, int c)
{
    do {
        if(*s != (char)c)
            continue;
        return s;
    } while(*s++);
    return NULL;
}

int strcmp(const char *sa, const char *sb)
{
    while(*sa && *sa == *sb) {
        sa++;
        sb++;
    }
    return *sa - *sb;
}

char *strcpy(char *sd, const char *ss)
{
    char *save = sd;
    while((*sd++ = *ss++));
    return save;
}

size_t strlen(const char *s)
{
    size_t i;
    for(i = 0; *s++; i++);
    return i;
}

char *strncat(char *sd, const char *ss, size_t n)
{
    char *save = sd;
    while(*sd)
        sd++;
    while(n && (*sd++ = *ss++))
        n--;
    if(n == 0)
        *sd = 0;
    return save;
}

int strncmp(const char *sa, const char *sb, size_t n)
{
    while(*sa && *sa == *sb && n--) {
        sa++;
        sb++;
    }
    return *sa - *sb;
}

char *strncpy(char *sd, const char *ss, size_t n)
{
    char *save = sd;
    while(n && (*sd++ = *ss++))
        n--;
    while(n-- > 1)
        *sd++ = 0;
    return save;
}

size_t strnlen(const char *s, size_t n)
{
    size_t i;
    for(i = 0; *s++ && i < n; i++);
    return i;
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

const char *strstr(const char *sa, const char *sb)
{
    const char *ap = sa;
    const char *bp;

    while(*sa) {
        bp = sb;
        while (*bp && (*ap == *bp)) {
            ++ap;
            ++bp;
        }
        if (!*bp)
            return sa;
        ++sa;
        ap = sa;
    }

    return NULL;
}


char *kstrncat(char *sd, const char *ss, size_t n)
{
    size_t nc;
    char *save = sd;
    while(*sd && n--)
        sd++;
    nc = strnlen(ss, --n);
    sd[nc] = 0;
    memcpy(sd, ss, nc);
    return save;
}

char *kstrncpy(char *sd, const char *ss, size_t n)
{
    char *save = sd;
    while(*ss && n--)
        *sd++ = *ss++;
    if(n)
        *sd = 0;
    return save;
}
