#include <ctype.h>

unsigned char ctype[] = {
    0x00,
    
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    
    CTYPE_CN,
    CTYPE_CN | CTYPE_WS,
    CTYPE_CN | CTYPE_WS,
    CTYPE_CN | CTYPE_WS,
    CTYPE_CN | CTYPE_WS,
    CTYPE_CN | CTYPE_WS,
    CTYPE_CN,
    CTYPE_CN,
    
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    CTYPE_CN,
    
    CTYPE_WS | CTYPE_HS,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_DD,
    
    CTYPE_DD,
    CTYPE_DD,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    
    CTYPE_PT,
    CTYPE_UC | CTYPE_XD,
    CTYPE_UC | CTYPE_XD,
    CTYPE_UC | CTYPE_XD,
    CTYPE_UC | CTYPE_XD,
    CTYPE_UC | CTYPE_XD,
    CTYPE_UC | CTYPE_XD,
    CTYPE_UC,
    
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_UC,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    
    CTYPE_PT,
    CTYPE_LC | CTYPE_XD,
    CTYPE_LC | CTYPE_XD,
    CTYPE_LC | CTYPE_XD,
    CTYPE_LC | CTYPE_XD,
    CTYPE_LC | CTYPE_XD,
    CTYPE_LC | CTYPE_XD,
    CTYPE_LC,
    
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_LC,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_PT,
    CTYPE_CN,

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
