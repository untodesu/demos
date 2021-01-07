#include <arch/types.h>
#include <ctype.h>

void * memset(void *s, int c, size_t n)
{
    register size_t i = n;

    if(i % sizeof(int) == 0) {
        register int *b = s;
        while(i -= sizeof(int))
            *b++ = c;
        return s;
    }

    register char *b = s;
    while(i--)
        *b++ = (char)c;
    return s;
}

void * memcpy(void *s1, const void *s2, size_t n)
{
    register size_t i = n;

    if(i % sizeof(int) == 0) {
        register int *b1 = s1;
        register const int *b2 = s2;
        while(i -= sizeof(int))
            *b1++ = *b2++;
        return s1;
    }

    register char *b1 = s1;
    register const char *b2 = s2;
    while(i--)
        *b1++ = *b2++;
    return s1;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    register size_t i = n;

    if(i % sizeof(int) == 0) {
        register const int *b1 = s1;
        register const int *b2 = s2;
        while(i -= sizeof(int)) {
            if(*b1 != *b2)
                return *b1 - *b2;
            b1++;
            b2++;
        }
        return 0;
    }

    register const char *b1 = s1;
    register const char *b2 = s2;
    while(i--) {
        if(*b1 != *b2)
            return *b1 - *b2;
        b1++;
        b2++;
    }
    return 0;
}

size_t strlen(const char *s)
{
    register size_t i = 0;
    register const char *sp = s;
    while(*sp++) i++;
    return i;
}

size_t strnlen(const char *s, size_t n)
{
    register size_t i = 0;
    register const char *sp = s;
    while(*sp++ && i < n) i++;
    return i;
}

char * strcpy(char *s1, const char *s2)
{
    register char *b1 = s1;
    register const char *b2 = s2;
    while(!!(*b1++ = *b2++));
    return s1;
}

char * strncpy(char *s1, const char *s2, size_t n)
{
    register char *b1 = s1;
    register const char *b2 = s2;
    register size_t i = n;
    while(*b2 && i--)
        *b1++ = *b2++;
    if(i) *b1 = 0;
    return s1;
}

int strcmp(const char *s1, const char *s2)
{
    register const char *b1 = s1;
    register const char *b2 = s2;
    while(*b1 && *b1 == *b2) {
        b1++;
        b2++;
    }
    return *b1 - *b2;
}

int stricmp(const char *s1, const char *s2)
{
    register const char *b1 = s1;
    register const char *b2 = s2;
    while(*b1 && tolower(*b1) == tolower(*b2)) {
        b1++;
        b2++;
    }
    return *b1 - *b2;
}

const char * strchr(const char *s, char c)
{
    register const char *sp = s;
    while(*sp)
        if(*sp++ == c) return sp;
    return NULL;
}

const char * strrchr(const char *s, char c)
{
    register const char *sp = s;
    register const char *chp = NULL;
    do {
        if(*sp == c)
            chp = sp;
    } while(*sp++);
    return chp;
}
