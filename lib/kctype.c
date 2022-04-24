/* SPDX-License-Identifier: BSD-2-Clause
 * Created: Sat Apr 23 2022 21:16:28 */
#include <kctype.h>

#define KCTYPE_NULL 0x000
#define KCTYPE_CTRL 0x001
#define KCTYPE_GRPH 0x002
#define KCTYPE_SPCE 0x004
#define KCTYPE_BLNK 0x008
#define KCTYPE_UPRC 0x010
#define KCTYPE_LWRC 0x020
#define KCTYPE_DECD 0x040
#define KCTYPE_HEXD 0x080
#define KCTYPE_PNCT 0x100

struct kctype_s {
    int lower, upper;
    unsigned int flags;
};

/* 256 characters plus EOF */
#define KCTYPE_SIZE 0x101

static const struct kctype_s kctype[KCTYPE_SIZE] = {
    /* EOF  */  { .lower = 0xFF, .upper = 0xFF, .flags = KCTYPE_NULL },
    /* NUL  */  { .lower = 0x00, .upper = 0x00, .flags = KCTYPE_CTRL },
    /* SOH  */  { .lower = 0x01, .upper = 0x01, .flags = KCTYPE_CTRL },
    /* STX  */  { .lower = 0x02, .upper = 0x02, .flags = KCTYPE_CTRL },
    /* ETX  */  { .lower = 0x03, .upper = 0x03, .flags = KCTYPE_CTRL },
    /* EOT  */  { .lower = 0x04, .upper = 0x04, .flags = KCTYPE_CTRL },
    /* ENQ  */  { .lower = 0x05, .upper = 0x05, .flags = KCTYPE_CTRL },
    /* ACK  */  { .lower = 0x06, .upper = 0x06, .flags = KCTYPE_CTRL },
    /* BEL  */  { .lower = 0x07, .upper = 0x07, .flags = KCTYPE_CTRL },
    /* BS   */  { .lower = 0x08, .upper = 0x08, .flags = KCTYPE_CTRL },
    /* HT   */  { .lower = 0x09, .upper = 0x09, .flags = KCTYPE_CTRL | KCTYPE_SPCE | KCTYPE_BLNK },
    /* LF   */  { .lower = 0x0A, .upper = 0x0A, .flags = KCTYPE_CTRL | KCTYPE_SPCE },
    /* VT   */  { .lower = 0x0B, .upper = 0x0B, .flags = KCTYPE_CTRL | KCTYPE_SPCE },
    /* FF   */  { .lower = 0x0C, .upper = 0x0C, .flags = KCTYPE_CTRL | KCTYPE_SPCE },
    /* CR   */  { .lower = 0x0D, .upper = 0x0D, .flags = KCTYPE_CTRL | KCTYPE_SPCE },
    /* SO   */  { .lower = 0x0E, .upper = 0x0E, .flags = KCTYPE_CTRL },
    /* SI   */  { .lower = 0x0F, .upper = 0x0F, .flags = KCTYPE_CTRL },
    /* DLE  */  { .lower = 0x10, .upper = 0x10, .flags = KCTYPE_CTRL },
    /* DC1  */  { .lower = 0x11, .upper = 0x11, .flags = KCTYPE_CTRL },
    /* DC2  */  { .lower = 0x12, .upper = 0x12, .flags = KCTYPE_CTRL },
    /* DC3  */  { .lower = 0x13, .upper = 0x13, .flags = KCTYPE_CTRL },
    /* DC4  */  { .lower = 0x14, .upper = 0x14, .flags = KCTYPE_CTRL },
    /* NAK  */  { .lower = 0x15, .upper = 0x15, .flags = KCTYPE_CTRL },
    /* SYN  */  { .lower = 0x16, .upper = 0x16, .flags = KCTYPE_CTRL },
    /* ETB  */  { .lower = 0x17, .upper = 0x17, .flags = KCTYPE_CTRL },
    /* CAN  */  { .lower = 0x18, .upper = 0x18, .flags = KCTYPE_CTRL },
    /* EM   */  { .lower = 0x19, .upper = 0x19, .flags = KCTYPE_CTRL },
    /* SUB  */  { .lower = 0x1A, .upper = 0x1A, .flags = KCTYPE_CTRL },
    /* ESC  */  { .lower = 0x1B, .upper = 0x1B, .flags = KCTYPE_CTRL },
    /* FS   */  { .lower = 0x1C, .upper = 0x1C, .flags = KCTYPE_CTRL },
    /* GS   */  { .lower = 0x1D, .upper = 0x1D, .flags = KCTYPE_CTRL },
    /* RS   */  { .lower = 0x1E, .upper = 0x1E, .flags = KCTYPE_CTRL },
    /* US   */  { .lower = 0x1F, .upper = 0x1F, .flags = KCTYPE_CTRL },
    /* SP   */  { .lower = 0x20, .upper = 0x20, .flags = KCTYPE_SPCE | KCTYPE_BLNK },
    /* !    */  { .lower = 0x21, .upper = 0x21, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* "    */  { .lower = 0x22, .upper = 0x22, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* #    */  { .lower = 0x23, .upper = 0x23, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* $    */  { .lower = 0x24, .upper = 0x24, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* %    */  { .lower = 0x25, .upper = 0x25, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* &    */  { .lower = 0x26, .upper = 0x26, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* '    */  { .lower = 0x27, .upper = 0x27, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* (    */  { .lower = 0x28, .upper = 0x28, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* )    */  { .lower = 0x29, .upper = 0x29, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* *    */  { .lower = 0x2A, .upper = 0x2A, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* +    */  { .lower = 0x2B, .upper = 0x2B, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* ,    */  { .lower = 0x2C, .upper = 0x2C, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* -    */  { .lower = 0x2D, .upper = 0x2D, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* .    */  { .lower = 0x2E, .upper = 0x2E, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* /    */  { .lower = 0x2F, .upper = 0x2F, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* 0    */  { .lower = 0x30, .upper = 0x30, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 1    */  { .lower = 0x31, .upper = 0x31, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 2    */  { .lower = 0x32, .upper = 0x32, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 3    */  { .lower = 0x33, .upper = 0x33, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 4    */  { .lower = 0x34, .upper = 0x34, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 5    */  { .lower = 0x35, .upper = 0x35, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 6    */  { .lower = 0x36, .upper = 0x36, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 7    */  { .lower = 0x37, .upper = 0x37, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 8    */  { .lower = 0x38, .upper = 0x38, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* 9    */  { .lower = 0x39, .upper = 0x39, .flags = KCTYPE_GRPH | KCTYPE_DECD | KCTYPE_HEXD },
    /* :    */  { .lower = 0x3A, .upper = 0x3A, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* ;    */  { .lower = 0x3B, .upper = 0x3B, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* <    */  { .lower = 0x3C, .upper = 0x3C, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* =    */  { .lower = 0x3D, .upper = 0x3D, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* >    */  { .lower = 0x3E, .upper = 0x3E, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* ?    */  { .lower = 0x3F, .upper = 0x3F, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* @    */  { .lower = 0x40, .upper = 0x40, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* A    */  { .lower = 0x61, .upper = 0x41, .flags = KCTYPE_GRPH | KCTYPE_UPRC | KCTYPE_HEXD },
    /* B    */  { .lower = 0x62, .upper = 0x42, .flags = KCTYPE_GRPH | KCTYPE_UPRC | KCTYPE_HEXD },
    /* C    */  { .lower = 0x63, .upper = 0x43, .flags = KCTYPE_GRPH | KCTYPE_UPRC | KCTYPE_HEXD },
    /* D    */  { .lower = 0x64, .upper = 0x44, .flags = KCTYPE_GRPH | KCTYPE_UPRC | KCTYPE_HEXD },
    /* E    */  { .lower = 0x65, .upper = 0x45, .flags = KCTYPE_GRPH | KCTYPE_UPRC | KCTYPE_HEXD },
    /* F    */  { .lower = 0x66, .upper = 0x46, .flags = KCTYPE_GRPH | KCTYPE_UPRC | KCTYPE_HEXD },
    /* G    */  { .lower = 0x67, .upper = 0x47, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* H    */  { .lower = 0x68, .upper = 0x48, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* I    */  { .lower = 0x69, .upper = 0x49, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* J    */  { .lower = 0x6A, .upper = 0x4A, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* K    */  { .lower = 0x6B, .upper = 0x4B, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* L    */  { .lower = 0x6C, .upper = 0x4C, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* M    */  { .lower = 0x6D, .upper = 0x4D, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* N    */  { .lower = 0x6E, .upper = 0x4E, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* O    */  { .lower = 0x6F, .upper = 0x4F, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* P    */  { .lower = 0x70, .upper = 0x50, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* Q    */  { .lower = 0x71, .upper = 0x51, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* R    */  { .lower = 0x72, .upper = 0x52, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* S    */  { .lower = 0x73, .upper = 0x53, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* T    */  { .lower = 0x74, .upper = 0x54, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* U    */  { .lower = 0x75, .upper = 0x55, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* V    */  { .lower = 0x76, .upper = 0x56, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* W    */  { .lower = 0x77, .upper = 0x57, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* X    */  { .lower = 0x78, .upper = 0x58, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* Y    */  { .lower = 0x79, .upper = 0x59, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* Z    */  { .lower = 0x7A, .upper = 0x5A, .flags = KCTYPE_GRPH | KCTYPE_UPRC },
    /* [    */  { .lower = 0x5B, .upper = 0x5B, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* \    */  { .lower = 0x5C, .upper = 0x5C, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* ]    */  { .lower = 0x5D, .upper = 0x5D, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* ^    */  { .lower = 0x5E, .upper = 0x5E, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* _    */  { .lower = 0x5F, .upper = 0x5F, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* `    */  { .lower = 0x60, .upper = 0x60, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* a    */  { .lower = 0x61, .upper = 0x41, .flags = KCTYPE_GRPH | KCTYPE_LWRC | KCTYPE_HEXD },
    /* b    */  { .lower = 0x62, .upper = 0x42, .flags = KCTYPE_GRPH | KCTYPE_LWRC | KCTYPE_HEXD },
    /* c    */  { .lower = 0x63, .upper = 0x43, .flags = KCTYPE_GRPH | KCTYPE_LWRC | KCTYPE_HEXD },
    /* d    */  { .lower = 0x64, .upper = 0x44, .flags = KCTYPE_GRPH | KCTYPE_LWRC | KCTYPE_HEXD },
    /* e    */  { .lower = 0x65, .upper = 0x45, .flags = KCTYPE_GRPH | KCTYPE_LWRC | KCTYPE_HEXD },
    /* f    */  { .lower = 0x66, .upper = 0x46, .flags = KCTYPE_GRPH | KCTYPE_LWRC | KCTYPE_HEXD },
    /* g    */  { .lower = 0x67, .upper = 0x47, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* h    */  { .lower = 0x68, .upper = 0x48, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* i    */  { .lower = 0x69, .upper = 0x49, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* j    */  { .lower = 0x6A, .upper = 0x4A, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* k    */  { .lower = 0x6B, .upper = 0x4B, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* l    */  { .lower = 0x6C, .upper = 0x4C, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* m    */  { .lower = 0x6D, .upper = 0x4D, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* n    */  { .lower = 0x6E, .upper = 0x4E, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* o    */  { .lower = 0x6F, .upper = 0x4F, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* p    */  { .lower = 0x70, .upper = 0x50, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* q    */  { .lower = 0x71, .upper = 0x51, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* r    */  { .lower = 0x72, .upper = 0x52, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* s    */  { .lower = 0x73, .upper = 0x53, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* t    */  { .lower = 0x74, .upper = 0x54, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* u    */  { .lower = 0x75, .upper = 0x55, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* v    */  { .lower = 0x76, .upper = 0x56, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* w    */  { .lower = 0x77, .upper = 0x57, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* x    */  { .lower = 0x78, .upper = 0x58, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* y    */  { .lower = 0x79, .upper = 0x59, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* z    */  { .lower = 0x7A, .upper = 0x5A, .flags = KCTYPE_GRPH | KCTYPE_LWRC },
    /* {    */  { .lower = 0x7B, .upper = 0x7B, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* |    */  { .lower = 0x7C, .upper = 0x7C, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* }    */  { .lower = 0x7D, .upper = 0x7D, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* ~    */  { .lower = 0x7E, .upper = 0x7E, .flags = KCTYPE_GRPH | KCTYPE_PNCT },
    /* DEL  */  { .lower = 0x7F, .upper = 0x7F, .flags = KCTYPE_CTRL },
    /*      */  { .lower = 0x80, .upper = 0x80, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x81, .upper = 0x81, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x82, .upper = 0x82, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x83, .upper = 0x83, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x84, .upper = 0x84, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x85, .upper = 0x85, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x86, .upper = 0x86, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x87, .upper = 0x87, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x88, .upper = 0x88, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x89, .upper = 0x89, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x8A, .upper = 0x8A, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x8B, .upper = 0x8B, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x8C, .upper = 0x8C, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x8D, .upper = 0x8D, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x8E, .upper = 0x8E, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x8F, .upper = 0x8F, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x90, .upper = 0x90, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x91, .upper = 0x91, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x92, .upper = 0x92, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x93, .upper = 0x93, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x94, .upper = 0x94, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x95, .upper = 0x95, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x96, .upper = 0x96, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x97, .upper = 0x97, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x98, .upper = 0x98, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x99, .upper = 0x99, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x9A, .upper = 0x9A, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x9B, .upper = 0x9B, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x9C, .upper = 0x9C, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x9D, .upper = 0x9D, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x9E, .upper = 0x9E, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0x9F, .upper = 0x9F, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA0, .upper = 0xA0, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA1, .upper = 0xA1, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA2, .upper = 0xA2, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA3, .upper = 0xA3, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA4, .upper = 0xA4, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA5, .upper = 0xA5, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA6, .upper = 0xA6, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA7, .upper = 0xA7, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA8, .upper = 0xA8, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xA9, .upper = 0xA9, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xAA, .upper = 0xAA, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xAB, .upper = 0xAB, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xAC, .upper = 0xAC, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xAD, .upper = 0xAD, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xAE, .upper = 0xAE, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xAF, .upper = 0xAF, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB0, .upper = 0xB0, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB1, .upper = 0xB1, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB2, .upper = 0xB2, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB3, .upper = 0xB3, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB4, .upper = 0xB4, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB5, .upper = 0xB5, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB6, .upper = 0xB6, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB7, .upper = 0xB7, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB8, .upper = 0xB8, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xB9, .upper = 0xB9, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xBA, .upper = 0xBA, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xBB, .upper = 0xBB, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xBC, .upper = 0xBC, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xBD, .upper = 0xBD, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xBE, .upper = 0xBE, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xBF, .upper = 0xBF, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC0, .upper = 0xC0, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC1, .upper = 0xC1, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC2, .upper = 0xC2, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC3, .upper = 0xC3, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC4, .upper = 0xC4, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC5, .upper = 0xC5, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC6, .upper = 0xC6, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC7, .upper = 0xC7, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC8, .upper = 0xC8, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xC9, .upper = 0xC9, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xCA, .upper = 0xCA, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xCB, .upper = 0xCB, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xCC, .upper = 0xCC, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xCD, .upper = 0xCD, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xCE, .upper = 0xCE, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xCF, .upper = 0xCF, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD0, .upper = 0xD0, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD1, .upper = 0xD1, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD2, .upper = 0xD2, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD3, .upper = 0xD3, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD4, .upper = 0xD4, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD5, .upper = 0xD5, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD6, .upper = 0xD6, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD7, .upper = 0xD7, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD8, .upper = 0xD8, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xD9, .upper = 0xD9, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xDA, .upper = 0xDA, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xDB, .upper = 0xDB, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xDC, .upper = 0xDC, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xDD, .upper = 0xDD, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xDE, .upper = 0xDE, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xDF, .upper = 0xDF, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE0, .upper = 0xE0, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE1, .upper = 0xE1, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE2, .upper = 0xE2, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE3, .upper = 0xE3, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE4, .upper = 0xE4, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE5, .upper = 0xE5, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE6, .upper = 0xE6, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE7, .upper = 0xE7, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE8, .upper = 0xE8, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xE9, .upper = 0xE9, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xEA, .upper = 0xEA, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xEB, .upper = 0xEB, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xEC, .upper = 0xEC, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xED, .upper = 0xED, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xEE, .upper = 0xEE, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xEF, .upper = 0xEF, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF0, .upper = 0xF0, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF1, .upper = 0xF1, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF2, .upper = 0xF2, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF3, .upper = 0xF3, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF4, .upper = 0xF4, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF5, .upper = 0xF5, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF6, .upper = 0xF6, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF7, .upper = 0xF7, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF8, .upper = 0xF8, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xF9, .upper = 0xF9, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xFA, .upper = 0xFA, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xFB, .upper = 0xFB, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xFC, .upper = 0xFC, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xFD, .upper = 0xFD, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xFE, .upper = 0xFE, .flags = KCTYPE_NULL },
    /*      */  { .lower = 0xFF, .upper = 0xFF, .flags = KCTYPE_NULL },
};

int kisalnum(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_UPRC | KCTYPE_LWRC | KCTYPE_DECD);
}

int kisalpha(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_UPRC | KCTYPE_LWRC);
}

int kisascii(int c)
{
    return (c & 0x7F) == c;
}

int kisblank(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_BLNK);
}

int kiscntrl(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_CTRL);
}

int kisdigit(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_DECD);
}

int kisgraph(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_GRPH);
}

int kislower(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_LWRC);
}

int kisprint(int c)
{
    if(c == ' ')
        return 1;
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_CTRL);
}

int kispunct(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_PNCT);
}

int kisspace(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_SPCE);
}

int kisupper(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_UPRC);
}

int kisxdigit(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].flags & (KCTYPE_HEXD);
}

int ktoascii(int c)
{
    return (c & 0x7F);
}

int ktolower(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].lower;
}

int ktoupper(int c)
{
    return kctype[(c + 1) % KCTYPE_SIZE].upper;
}
