/* SPDX-License-Identifier: BSD-2-Clause */
#ifndef _STDINT_H_
#define _STDINT_H_ 1

#define INT8_C      __INT8_C
#define INT16_C     __INT16_C
#define INT32_C     __INT32_C
#define INT64_C     __INT64_C
#define INTMAX_C    __INTMAX_C

#define UINT8_C     __UINT8_C
#define UINT16_C    __UINT16_C
#define UINT32_C    __UINT32_C
#define UINT64_C    __UINT64_C
#define UINTMAX_C   __UINTMAX_C

#define INT8_MAX    ((__INT8_TYPE__)(__INT8_MAX__))
#define INT16_MAX   ((__INT16_TYPE__)(__INT16_MAX__))
#define INT32_MAX   ((__INT32_TYPE__)(__INT32_MAX__))
#define INT64_MAX   ((__INT64_TYPE__)(__INT64_MAX__))
#define INTMAX_MAX  ((__INTMAX_TYPE__)(__INTMAX_MAX__))
#define INTPTR_MAX  ((__INTPTR_TYPE__)(__INTPTR_MAX__))

#define INT8_MIN    ((__INT8_TYPE__)(-__INT8_MAX__ - 1))
#define INT16_MIN   ((__INT16_TYPE__)(-__INT16_MAX__ - 1))
#define INT32_MIN   ((__INT32_TYPE__)(-__INT32_MAX__ - 1))
#define INT64_MIN   ((__INT64_TYPE__)(-__INT64_MAX__ - 1))
#define INTMAX_MIN  ((__INTMAX_TYPE__)(-__INTMAX_MAX__ - 1))
#define INTPTR_MIN  ((__INTPTR_TYPE__)(-__INTPTR_MAX__ - 1))

#define UINT8_MAX   ((__UINT8_TYPE__)(__UINT8_MAX__))
#define UINT16_MAX  ((__UINT16_TYPE__)(__UINT16_MAX__))
#define UINT32_MAX  ((__UINT32_TYPE__)(__UINT32_MAX__))
#define UINT64_MAX  ((__UINT64_TYPE__)(__UINT64_MAX__))
#define UINTMAX_MAX ((__UINTMAX_TYPE__)(__UINTMAX_MAX__))
#define UINTPTR_MAX ((__UINTPTR_TYPE__)(__UINTPTR_MAX__))
#define SIZE_MAX    ((__SIZE_TYPE__)(__SIZE_MAX__))

typedef __INT8_TYPE__       int8_t;
typedef __INT16_TYPE__      int16_t;
typedef __INT32_TYPE__      int32_t;
typedef __INT64_TYPE__      int64_t;
typedef __INTMAX_TYPE__     intmax_t;
typedef __INTPTR_TYPE__     intptr_t;

typedef __UINT8_TYPE__      uint8_t;
typedef __UINT16_TYPE__     uint16_t;
typedef __UINT32_TYPE__     uint32_t;
typedef __UINT64_TYPE__     uint64_t;
typedef __UINTMAX_TYPE__    uintmax_t;
typedef __UINTPTR_TYPE__    uintptr_t;

#endif
