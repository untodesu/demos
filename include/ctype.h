#ifndef _CTYPE_H_
#define _CTYPE_H_ 1

#define _CTYPE_UC 0x01
#define _CTYPE_LC 0x02
#define _CTYPE_DD 0x04
#define _CTYPE_CN 0x08
#define _CTYPE_PT 0x10
#define _CTYPE_WS 0x20
#define _CTYPE_XD 0x40
#define _CTYPE_HS 0x80

extern unsigned char _ctype[];

#define isalnum(c)  (_ctype[(c) + 1] & (_CTYPE_UC | _CTYPE_LC | _CTYPE_DD))
#define isalpha(c)  (_ctype[(c) + 1] & (_CTYPE_UC | _CTYPE_LC))
#define iscntrl(c)  (_ctype[(c) + 1] & (_CTYPE_CN))
#define isdigit(c)  (_ctype[(c) + 1] & (_CTYPE_DD))
#define isgraph(c)  (_ctype[(c) + 1] & (_CTYPE_PT | _CTYPE_UC | _CTYPE_LC | _CTYPE_DD))
#define islower(c)  (_ctype[(c) + 1] & (_CTYPE_LC))
#define isprint(c)  (_ctype[(c) + 1] & (_CTYPE_PT | _CTYPE_UC | _CTYPE_LC | _CTYPE_DD | _CTYPE_HS))
#define ispunct(c)  (_ctype[(c) + 1] & (_CTYPE_PT))
#define isspace(c)  (_ctype[(c) + 1] & (_CTYPE_WS))
#define isupper(c)  (_ctype[(c) + 1] & (_CTYPE_UC))
#define isxdigit(c) (_ctype[(c) + 1] & (_CTYPE_DD | _CTYPE_XD))

int isascii(int c);
int toascii(int c);
int tolower(int c);
int toupper(int c);

#endif
