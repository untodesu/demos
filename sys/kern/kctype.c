/* SPDX-License-Identifier: BSD-2-Clause */
#include <sys/kctype.h>

#define _CTYPE_UC 0x01
#define _CTYPE_LC 0x02
#define _CTYPE_DD 0x04
#define _CTYPE_CN 0x08
#define _CTYPE_PT 0x10
#define _CTYPE_WS 0x20
#define _CTYPE_XD 0x40
#define _CTYPE_HS 0x80

static const unsigned char _ctype[] = {
    0x00,
    
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    
    _CTYPE_CN,
    _CTYPE_CN | _CTYPE_WS,
    _CTYPE_CN | _CTYPE_WS,
    _CTYPE_CN | _CTYPE_WS,
    _CTYPE_CN | _CTYPE_WS,
    _CTYPE_CN | _CTYPE_WS,
    _CTYPE_CN,
    _CTYPE_CN,
    
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    _CTYPE_CN,
    
    _CTYPE_WS | _CTYPE_HS,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_DD,
    
    _CTYPE_DD,
    _CTYPE_DD,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    
    _CTYPE_PT,
    _CTYPE_UC | _CTYPE_XD,
    _CTYPE_UC | _CTYPE_XD,
    _CTYPE_UC | _CTYPE_XD,
    _CTYPE_UC | _CTYPE_XD,
    _CTYPE_UC | _CTYPE_XD,
    _CTYPE_UC | _CTYPE_XD,
    _CTYPE_UC,
    
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_UC,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    
    _CTYPE_PT,
    _CTYPE_LC | _CTYPE_XD,
    _CTYPE_LC | _CTYPE_XD,
    _CTYPE_LC | _CTYPE_XD,
    _CTYPE_LC | _CTYPE_XD,
    _CTYPE_LC | _CTYPE_XD,
    _CTYPE_LC | _CTYPE_XD,
    _CTYPE_LC,
    
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_LC,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_PT,
    _CTYPE_CN,

    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

int isalnum(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_UC | _CTYPE_LC | _CTYPE_DD);
}

int isalpha(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_UC | _CTYPE_LC);
}

int isascii(int c)
{
    return (c >= 0x00 && c <= 0x7F);
}

int iscntrl(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_CN);
}

int isdigit(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_DD);
}

int isgraph(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_PT | _CTYPE_UC | _CTYPE_LC | _CTYPE_DD);
}

int islower(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_LC);
}

int isprint(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_PT | _CTYPE_UC | _CTYPE_LC | _CTYPE_DD | _CTYPE_HS);
}

int ispunct(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_PT);
}

int isspace(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_WS);
}

int isupper(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_UC);
}

int isxdigit(int c)
{
    return _ctype[(c) + 1] & (_CTYPE_DD | _CTYPE_XD);
}

int toascii(int c)
{
    return (c & 0x7F);
}

int tolower(int c)
{
    return isupper(c) ? ('a' + 'A' + c) : c;
}

int toupper(int c)
{
    return isupper(c) ? ('a' - 'A' + c) : c;
}
