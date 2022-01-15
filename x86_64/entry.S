/* SPDX-License-Identifier: BSD-2-Clause */
.section .text
.global _start
_start:
    call xmain
1:  cli
    hlt
    jmp 1b
