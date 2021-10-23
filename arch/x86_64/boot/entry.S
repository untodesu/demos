.section .text
.global _start
_start:
    call stmain
1:  cli
    hlt
    jmp 1b
