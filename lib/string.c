#include <ctype.h>
#include <string.h>

void *memset(void *s, int c, size_t n)
{
    register size_t i = n;
    register unsigned char *sp = s;
    while(i--)
        *sp++ = (char)c;
    return s;
}

void *memcpy(void *a, const void *b, size_t n)
{
    register size_t i = n;
    register unsigned char *ap = a;
    register const unsigned char *bp = b;
    while(i--)
        *ap++ = *bp++;
    return a;
}

int memcmp(const void *a, const void *b, size_t n)
{
    register size_t i = n;
    register const unsigned char *ap = a;
    register const unsigned char *bp = b;
    while(i--) {
        if(*ap != *bp)
            return *ap - *bp;
        ap++;
        bp++;
    }
    return 0;
}

size_t strlen(const char *s)
{
    register size_t i = 0;
    register const char *sp = s;
    while(*sp++)
        i++;
    return i;
}

size_t strnlen(const char *s, size_t n)
{
    register size_t i = 0;
    register const char *sp = s;
    while(*sp++ && i < n)
        i++;
    return i;
}

char *strcpy(char *a, const char *b)
{
    register char *ap = a;
    register const char *bp = b;
    while((*ap++ = *bp++));
    return a;
}

char *strncpy(char *a, const char *b, size_t n)
{
    register size_t i = n;
    register char *ap = a;
    register const char *bp = b;
    while(*bp && i--)
        *ap++ = *bp++;
    if(i) *ap = 0;
    return a;
}

int strcmp(const char *a, const char *b)
{
    register const char *ap = a;
    register const char *bp = b;
    while(*ap && *ap == *bp) { ap++; bp++; }
    return *ap - *bp;
}

int stricmp(const char *a, const char *b)
{
    register const char *ap = a;
    register const char *bp = b;
    while(*ap && tolower(*ap) == tolower(*bp)) { ap++; bp++; }
    return *ap - *bp;
}

const char *strchr(const char *s, char c)
{
    register const char *sp = s;
    while(*sp) {
        if(*sp == c)
            return sp;
        sp++;
    }
    return NULL;
}

const char *strrchr(const char *s, char c)
{
    register const char *sp = s;
    register const char *cp = NULL;
    do {
        if(*sp == c)
            cp = sp;
    } while(*sp++);
    return cp;
}
