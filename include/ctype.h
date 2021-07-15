#ifndef CTYPE_H
#define CTYPE_H 1

#define CTYPE_UC 0x01
#define CTYPE_LC 0x02
#define CTYPE_DD 0x04
#define CTYPE_CN 0x08
#define CTYPE_PT 0x10
#define CTYPE_WS 0x20
#define CTYPE_XD 0x40
#define CTYPE_HS 0x80

extern unsigned char ctype[];

#define isalnum(c)  (ctype[(c) + 1] & (CTYPE_UC | CTYPE_LC | CTYPE_DD))
#define isalpha(c)  (ctype[(c) + 1] & (CTYPE_UC | CTYLE_LC))
#define iscntrl(c)  (ctype[(c) + 1] & (CTYPE_CN))
#define isdigit(c)  (ctype[(c) + 1] & (CTYPE_DD))
#define isgraph(c)  (ctype[(c) + 1] & (CTYPE_PT | CTYPE_UC | CTYPE_LC | CTYPE_DD))
#define islower(c)  (ctype[(c) + 1] & (CTYPE_LC))
#define isprint(c)  (ctype[(c) + 1] & (CTYPE_PT | CTYPE_UC | CTYPE_LC | CTYPE_DD | CTYPE_HS))
#define ispunct(c)  (ctype[(c) + 1] & (CTYPE_PT))
#define isspace(c)  (ctype[(c) + 1] & (CTYPE_WS))
#define isupper(c)  (ctype[(c) + 1] & (CTYPE_UC))
#define isxdigit(c) (ctype[(c) + 1] & (CTYPE_DD | CTYPE_XD))

int isascii(int c);
int toascii(int c);
int tolower(int c);
int toupper(int c);

#endif
