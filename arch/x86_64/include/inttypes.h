#ifndef _INTTYPES_H_
#define _INTTYPES_H_ 1

/* UNDONE: this lacks virtually
 * anything except stdint.h part */

#define INT8_MIN        -127
#define INT16_MIN       -32767
#define INT32_MIN       -2147483647
#define INT64_MIN       -9223372036854775807
#define INT_LEAST8_MIN  -2147483647
#define INT_LEAST16_MIN -2147483647
#define INT_LEAST32_MIN -2147483647
#define INT_LEAST64_MIN -9223372036854775807
#define INT_FAST8_MIN   -2147483647
#define INT_FAST16_MIN  -2147483647
#define INT_FAST32_MIN  -2147483647
#define INT_FAST64_MIN  -9223372036854775807
#define INTMAX_MIN      -9223372036854775807
#define INTPTR_MIN      -9223372036854775807

#define INT8_MAX        127
#define INT16_MAX       32767
#define INT32_MAX       2147483647
#define INT64_MAX       9223372036854775807
#define INT_LEAST8_MAX  2147483647
#define INT_LEAST16_MAX 2147483647
#define INT_LEAST32_MAX 2147483647
#define INT_LEAST64_MAX 9223372036854775807
#define INT_FAST8_MAX   2147483647
#define INT_FAST16_MAX  2147483647
#define INT_FAST32_MAX  2147483647
#define INT_FAST64_MAX  9223372036854775807
#define INTMAX_MAX      9223372036854775807
#define INTPTR_MAX      9223372036854775807

#define UINT8_MAX       255
#define UINT16_MAX      65535
#define UINT32_MAX      4294967295
#define UINT64_MAX      18446744073709551615
#define UINTMAX_MAX     18446744073709551615
#define UINTPTR_MAX     18446744073709551615

#define SIZE_MAX        18446744073709551615

typedef signed char         int8_t;
typedef signed short int    int16_t;
typedef signed int          int32_t;
typedef signed long int     int64_t;
typedef signed long int     intmax_t;
typedef signed long int     intptr_t;

typedef signed int          int_least8_t;
typedef signed int          int_least16_t;
typedef signed int          int_least32_t;
typedef signed long int     int_least64_t;

typedef signed int          int_fast8_t;
typedef signed int          int_fast16_t;
typedef signed int          int_fast32_t;
typedef signed long int     int_fast64_t;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long int   uint64_t;
typedef unsigned long int   uintmax_t;
typedef unsigned long int   uintptr_t;

typedef unsigned int        uint_least8_t;
typedef unsigned int        uint_least16_t;
typedef unsigned int        uint_least32_t;
typedef unsigned long int   uint_least64_t;

typedef unsigned int        uint_fast8_t;
typedef unsigned int        uint_fast16_t;
typedef unsigned int        uint_fast32_t;
typedef unsigned long int   uint_fast64_t;

#endif
