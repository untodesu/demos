#ifndef __CTYPE_H__
#define __CTYPE_H__ 1

#define _CTYPE_UC 0x01
#define _CTYPE_LC 0x02
#define _CTYPE_DD 0x04
#define _CTYPE_CN 0x08
#define _CTYPE_PT 0x10
#define _CTYPE_WS 0x20
#define _CTYPE_XD 0x40
#define _CTYPE_HS 0x80

extern unsigned char _ctype[];

static inline int isalnum(int c)
{
    return _ctype[c + 1] & (_CTYPE_UC | _CTYPE_LC | _CTYPE_DD);
}

static inline int isalpha(int c)
{
    return _ctype[c + 1] & (_CTYPE_UC | _CTYPE_LC);
}

static inline int iscntrl(int c)
{
    return _ctype[c + 1] & (_CTYPE_CN);
}

static inline int isdigit(int c)
{
    return _ctype[c + 1] & (_CTYPE_DD);
}

static inline int isgraph(int c)
{
    return _ctype[c + 1] & (_CTYPE_PT | _CTYPE_UC | _CTYPE_LC | _CTYPE_DD);
}

static inline int islower(int c)
{
    return _ctype[c + 1] & (_CTYPE_LC);
}

static inline int isprint(int c)
{
    return _ctype[c + 1] & (_CTYPE_PT | _CTYPE_UC | _CTYPE_LC | _CTYPE_DD | _CTYPE_HS);
}

static inline int ispunct(int c)
{
    return _ctype[c + 1] & (_CTYPE_PT);
}

static inline int isspace(int c)
{
    return _ctype[c + 1] & (_CTYPE_WS);
}

static inline int isupper(int c)
{
    return _ctype[c + 1] & (_CTYPE_UC);
}

static inline int isxdigit(int c)
{
    return _ctype[c + 1] & (_CTYPE_DD | _CTYPE_XD);
}

static inline int isascii(int c)
{
    return (c >= 0x00 && c <= 0x7F);
}

static inline int toascii(int c)
{
    return (c & 0x7F);
}

static inline int tolower(int c)
{
    return isupper(c) ? ('a' + 'A' + c) : c;
}

static inline int toupper(int c)
{
    return isupper(c) ? ('a' - 'A' + c) : c;
}

#endif
