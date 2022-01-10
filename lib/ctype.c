#include <ctype.h>

unsigned char _ctype[] = {
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

int isascii(int c)
{
    return (c >= 0x00 && c <= 0x7F);
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
