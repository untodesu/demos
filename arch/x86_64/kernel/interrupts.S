#include <arch/segment.h>

.section .text
interrupt_xx:
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rbp
    pushq %rsi
    pushq %rdi

    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    mov %rsp, %rdi
    call common_interrupt_handler

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8

    popq %rdi
    popq %rsi
    popq %rbp
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax

    addq $16, %rsp

    sti
    iretq

.macro DECLARE_INTR_PUSH1 N1, N2
.global \N1
\N1:
    cli
    pushq $0
    pushq $\N2
    jmp interrupt_xx
.endm

.macro DECLARE_TRAP_PUSH1 N1, N2
.global \N1
\N1:
    pushq $\N2
    jmp interrupt_xx
.endm

.macro DECLARE_TRAP_PUSH2 N1, N2
.global \N1
\N1:
    pushq $0
    pushq $\N2
    jmp interrupt_xx
.endm

DECLARE_TRAP_PUSH2 interrupt_00, 0x00 // division by zero
DECLARE_TRAP_PUSH2 interrupt_01, 0x01 // debug exception
DECLARE_INTR_PUSH1 interrupt_02, 0x02 // non-maskable interrupt
DECLARE_TRAP_PUSH2 interrupt_03, 0x03 // breakpoint
DECLARE_TRAP_PUSH2 interrupt_04, 0x04 // overflow
DECLARE_TRAP_PUSH2 interrupt_05, 0x05 // bound range exceeded
DECLARE_TRAP_PUSH2 interrupt_06, 0x06 // invalid opcode
DECLARE_TRAP_PUSH2 interrupt_07, 0x07 // device not available
DECLARE_TRAP_PUSH1 interrupt_08, 0x08 // double fault
DECLARE_TRAP_PUSH2 interrupt_09, 0x09 // coprocessor segment overrun (unused, reserved)
DECLARE_TRAP_PUSH1 interrupt_0A, 0x0A // invalid tss
DECLARE_TRAP_PUSH1 interrupt_0B, 0x0B // segment not present
DECLARE_TRAP_PUSH1 interrupt_0C, 0x0C // stack-segment fault
DECLARE_TRAP_PUSH1 interrupt_0D, 0x0D // general protection fault
DECLARE_TRAP_PUSH1 interrupt_0E, 0x0E // page fault
DECLARE_TRAP_PUSH2 interrupt_0F, 0x0F // reserved
DECLARE_TRAP_PUSH2 interrupt_10, 0x10 // x87 FP exception
DECLARE_TRAP_PUSH2 interrupt_11, 0x11 // alignment check
DECLARE_TRAP_PUSH2 interrupt_12, 0x12 // machine check
DECLARE_TRAP_PUSH2 interrupt_13, 0x13 // SIMD FP exception
DECLARE_TRAP_PUSH2 interrupt_14, 0x14 // virtualization exception
DECLARE_TRAP_PUSH2 interrupt_15, 0x15 // reserved
DECLARE_TRAP_PUSH2 interrupt_16, 0x16 // reserved
DECLARE_TRAP_PUSH2 interrupt_17, 0x17 // reserved
DECLARE_TRAP_PUSH2 interrupt_18, 0x18 // reserved
DECLARE_TRAP_PUSH2 interrupt_19, 0x19 // reserved
DECLARE_TRAP_PUSH2 interrupt_1A, 0x1A // reserved
DECLARE_TRAP_PUSH2 interrupt_1B, 0x1B // reserved
DECLARE_TRAP_PUSH2 interrupt_1C, 0x1C // reserved
DECLARE_TRAP_PUSH2 interrupt_1D, 0x1D // reserved
DECLARE_TRAP_PUSH2 interrupt_1E, 0x1E // security exception
DECLARE_TRAP_PUSH2 interrupt_1F, 0x1F // reserved
DECLARE_INTR_PUSH1 interrupt_20, 0x20
DECLARE_INTR_PUSH1 interrupt_21, 0x21
DECLARE_INTR_PUSH1 interrupt_22, 0x22
DECLARE_INTR_PUSH1 interrupt_23, 0x23
DECLARE_INTR_PUSH1 interrupt_24, 0x24
DECLARE_INTR_PUSH1 interrupt_25, 0x25
DECLARE_INTR_PUSH1 interrupt_26, 0x26
DECLARE_INTR_PUSH1 interrupt_27, 0x27
DECLARE_INTR_PUSH1 interrupt_28, 0x28
DECLARE_INTR_PUSH1 interrupt_29, 0x29
DECLARE_INTR_PUSH1 interrupt_2A, 0x2A
DECLARE_INTR_PUSH1 interrupt_2B, 0x2B
DECLARE_INTR_PUSH1 interrupt_2C, 0x2C
DECLARE_INTR_PUSH1 interrupt_2D, 0x2D
DECLARE_INTR_PUSH1 interrupt_2E, 0x2E
DECLARE_INTR_PUSH1 interrupt_2F, 0x2F
DECLARE_INTR_PUSH1 interrupt_30, 0x30
DECLARE_INTR_PUSH1 interrupt_31, 0x31
DECLARE_INTR_PUSH1 interrupt_32, 0x32
DECLARE_INTR_PUSH1 interrupt_33, 0x33
DECLARE_INTR_PUSH1 interrupt_34, 0x34
DECLARE_INTR_PUSH1 interrupt_35, 0x35
DECLARE_INTR_PUSH1 interrupt_36, 0x36
DECLARE_INTR_PUSH1 interrupt_37, 0x37
DECLARE_INTR_PUSH1 interrupt_38, 0x38
DECLARE_INTR_PUSH1 interrupt_39, 0x39
DECLARE_INTR_PUSH1 interrupt_3A, 0x3A
DECLARE_INTR_PUSH1 interrupt_3B, 0x3B
DECLARE_INTR_PUSH1 interrupt_3C, 0x3C
DECLARE_INTR_PUSH1 interrupt_3D, 0x3D
DECLARE_INTR_PUSH1 interrupt_3E, 0x3E
DECLARE_INTR_PUSH1 interrupt_3F, 0x3F
DECLARE_INTR_PUSH1 interrupt_40, 0x40
DECLARE_INTR_PUSH1 interrupt_41, 0x41
DECLARE_INTR_PUSH1 interrupt_42, 0x42
DECLARE_INTR_PUSH1 interrupt_43, 0x43
DECLARE_INTR_PUSH1 interrupt_44, 0x44
DECLARE_INTR_PUSH1 interrupt_45, 0x45
DECLARE_INTR_PUSH1 interrupt_46, 0x46
DECLARE_INTR_PUSH1 interrupt_47, 0x47
DECLARE_INTR_PUSH1 interrupt_48, 0x48
DECLARE_INTR_PUSH1 interrupt_49, 0x49
DECLARE_INTR_PUSH1 interrupt_4A, 0x4A
DECLARE_INTR_PUSH1 interrupt_4B, 0x4B
DECLARE_INTR_PUSH1 interrupt_4C, 0x4C
DECLARE_INTR_PUSH1 interrupt_4D, 0x4D
DECLARE_INTR_PUSH1 interrupt_4E, 0x4E
DECLARE_INTR_PUSH1 interrupt_4F, 0x4F
DECLARE_INTR_PUSH1 interrupt_50, 0x50
DECLARE_INTR_PUSH1 interrupt_51, 0x51
DECLARE_INTR_PUSH1 interrupt_52, 0x52
DECLARE_INTR_PUSH1 interrupt_53, 0x53
DECLARE_INTR_PUSH1 interrupt_54, 0x54
DECLARE_INTR_PUSH1 interrupt_55, 0x55
DECLARE_INTR_PUSH1 interrupt_56, 0x56
DECLARE_INTR_PUSH1 interrupt_57, 0x57
DECLARE_INTR_PUSH1 interrupt_58, 0x58
DECLARE_INTR_PUSH1 interrupt_59, 0x59
DECLARE_INTR_PUSH1 interrupt_5A, 0x5A
DECLARE_INTR_PUSH1 interrupt_5B, 0x5B
DECLARE_INTR_PUSH1 interrupt_5C, 0x5C
DECLARE_INTR_PUSH1 interrupt_5D, 0x5D
DECLARE_INTR_PUSH1 interrupt_5E, 0x5E
DECLARE_INTR_PUSH1 interrupt_5F, 0x5F
DECLARE_INTR_PUSH1 interrupt_60, 0x60
DECLARE_INTR_PUSH1 interrupt_61, 0x61
DECLARE_INTR_PUSH1 interrupt_62, 0x62
DECLARE_INTR_PUSH1 interrupt_63, 0x63
DECLARE_INTR_PUSH1 interrupt_64, 0x64
DECLARE_INTR_PUSH1 interrupt_65, 0x65
DECLARE_INTR_PUSH1 interrupt_66, 0x66
DECLARE_INTR_PUSH1 interrupt_67, 0x67
DECLARE_INTR_PUSH1 interrupt_68, 0x68
DECLARE_INTR_PUSH1 interrupt_69, 0x69
DECLARE_INTR_PUSH1 interrupt_6A, 0x6A
DECLARE_INTR_PUSH1 interrupt_6B, 0x6B
DECLARE_INTR_PUSH1 interrupt_6C, 0x6C
DECLARE_INTR_PUSH1 interrupt_6D, 0x6D
DECLARE_INTR_PUSH1 interrupt_6E, 0x6E
DECLARE_INTR_PUSH1 interrupt_6F, 0x6F
DECLARE_INTR_PUSH1 interrupt_70, 0x70
DECLARE_INTR_PUSH1 interrupt_71, 0x71
DECLARE_INTR_PUSH1 interrupt_72, 0x72
DECLARE_INTR_PUSH1 interrupt_73, 0x73
DECLARE_INTR_PUSH1 interrupt_74, 0x74
DECLARE_INTR_PUSH1 interrupt_75, 0x75
DECLARE_INTR_PUSH1 interrupt_76, 0x76
DECLARE_INTR_PUSH1 interrupt_77, 0x77
DECLARE_INTR_PUSH1 interrupt_78, 0x78
DECLARE_INTR_PUSH1 interrupt_79, 0x79
DECLARE_INTR_PUSH1 interrupt_7A, 0x7A
DECLARE_INTR_PUSH1 interrupt_7B, 0x7B
DECLARE_INTR_PUSH1 interrupt_7C, 0x7C
DECLARE_INTR_PUSH1 interrupt_7D, 0x7D
DECLARE_INTR_PUSH1 interrupt_7E, 0x7E
DECLARE_INTR_PUSH1 interrupt_7F, 0x7F
DECLARE_INTR_PUSH1 interrupt_80, 0x80
DECLARE_INTR_PUSH1 interrupt_81, 0x81
DECLARE_INTR_PUSH1 interrupt_82, 0x82
DECLARE_INTR_PUSH1 interrupt_83, 0x83
DECLARE_INTR_PUSH1 interrupt_84, 0x84
DECLARE_INTR_PUSH1 interrupt_85, 0x85
DECLARE_INTR_PUSH1 interrupt_86, 0x86
DECLARE_INTR_PUSH1 interrupt_87, 0x87
DECLARE_INTR_PUSH1 interrupt_88, 0x88
DECLARE_INTR_PUSH1 interrupt_89, 0x89
DECLARE_INTR_PUSH1 interrupt_8A, 0x8A
DECLARE_INTR_PUSH1 interrupt_8B, 0x8B
DECLARE_INTR_PUSH1 interrupt_8C, 0x8C
DECLARE_INTR_PUSH1 interrupt_8D, 0x8D
DECLARE_INTR_PUSH1 interrupt_8E, 0x8E
DECLARE_INTR_PUSH1 interrupt_8F, 0x8F
DECLARE_INTR_PUSH1 interrupt_90, 0x90
DECLARE_INTR_PUSH1 interrupt_91, 0x91
DECLARE_INTR_PUSH1 interrupt_92, 0x92
DECLARE_INTR_PUSH1 interrupt_93, 0x93
DECLARE_INTR_PUSH1 interrupt_94, 0x94
DECLARE_INTR_PUSH1 interrupt_95, 0x95
DECLARE_INTR_PUSH1 interrupt_96, 0x96
DECLARE_INTR_PUSH1 interrupt_97, 0x97
DECLARE_INTR_PUSH1 interrupt_98, 0x98
DECLARE_INTR_PUSH1 interrupt_99, 0x99
DECLARE_INTR_PUSH1 interrupt_9A, 0x9A
DECLARE_INTR_PUSH1 interrupt_9B, 0x9B
DECLARE_INTR_PUSH1 interrupt_9C, 0x9C
DECLARE_INTR_PUSH1 interrupt_9D, 0x9D
DECLARE_INTR_PUSH1 interrupt_9E, 0x9E
DECLARE_INTR_PUSH1 interrupt_9F, 0x9F
DECLARE_INTR_PUSH1 interrupt_A0, 0xA0
DECLARE_INTR_PUSH1 interrupt_A1, 0xA1
DECLARE_INTR_PUSH1 interrupt_A2, 0xA2
DECLARE_INTR_PUSH1 interrupt_A3, 0xA3
DECLARE_INTR_PUSH1 interrupt_A4, 0xA4
DECLARE_INTR_PUSH1 interrupt_A5, 0xA5
DECLARE_INTR_PUSH1 interrupt_A6, 0xA6
DECLARE_INTR_PUSH1 interrupt_A7, 0xA7
DECLARE_INTR_PUSH1 interrupt_A8, 0xA8
DECLARE_INTR_PUSH1 interrupt_A9, 0xA9
DECLARE_INTR_PUSH1 interrupt_AA, 0xAA
DECLARE_INTR_PUSH1 interrupt_AB, 0xAB
DECLARE_INTR_PUSH1 interrupt_AC, 0xAC
DECLARE_INTR_PUSH1 interrupt_AD, 0xAD
DECLARE_INTR_PUSH1 interrupt_AE, 0xAE
DECLARE_INTR_PUSH1 interrupt_AF, 0xAF
DECLARE_INTR_PUSH1 interrupt_B0, 0xB0
DECLARE_INTR_PUSH1 interrupt_B1, 0xB1
DECLARE_INTR_PUSH1 interrupt_B2, 0xB2
DECLARE_INTR_PUSH1 interrupt_B3, 0xB3
DECLARE_INTR_PUSH1 interrupt_B4, 0xB4
DECLARE_INTR_PUSH1 interrupt_B5, 0xB5
DECLARE_INTR_PUSH1 interrupt_B6, 0xB6
DECLARE_INTR_PUSH1 interrupt_B7, 0xB7
DECLARE_INTR_PUSH1 interrupt_B8, 0xB8
DECLARE_INTR_PUSH1 interrupt_B9, 0xB9
DECLARE_INTR_PUSH1 interrupt_BA, 0xBA
DECLARE_INTR_PUSH1 interrupt_BB, 0xBB
DECLARE_INTR_PUSH1 interrupt_BC, 0xBC
DECLARE_INTR_PUSH1 interrupt_BD, 0xBD
DECLARE_INTR_PUSH1 interrupt_BE, 0xBE
DECLARE_INTR_PUSH1 interrupt_BF, 0xBF
DECLARE_INTR_PUSH1 interrupt_C0, 0xC0
DECLARE_INTR_PUSH1 interrupt_C1, 0xC1
DECLARE_INTR_PUSH1 interrupt_C2, 0xC2
DECLARE_INTR_PUSH1 interrupt_C3, 0xC3
DECLARE_INTR_PUSH1 interrupt_C4, 0xC4
DECLARE_INTR_PUSH1 interrupt_C5, 0xC5
DECLARE_INTR_PUSH1 interrupt_C6, 0xC6
DECLARE_INTR_PUSH1 interrupt_C7, 0xC7
DECLARE_INTR_PUSH1 interrupt_C8, 0xC8
DECLARE_INTR_PUSH1 interrupt_C9, 0xC9
DECLARE_INTR_PUSH1 interrupt_CA, 0xCA
DECLARE_INTR_PUSH1 interrupt_CB, 0xCB
DECLARE_INTR_PUSH1 interrupt_CC, 0xCC
DECLARE_INTR_PUSH1 interrupt_CD, 0xCD
DECLARE_INTR_PUSH1 interrupt_CE, 0xCE
DECLARE_INTR_PUSH1 interrupt_CF, 0xCF
DECLARE_INTR_PUSH1 interrupt_D0, 0xD0
DECLARE_INTR_PUSH1 interrupt_D1, 0xD1
DECLARE_INTR_PUSH1 interrupt_D2, 0xD2
DECLARE_INTR_PUSH1 interrupt_D3, 0xD3
DECLARE_INTR_PUSH1 interrupt_D4, 0xD4
DECLARE_INTR_PUSH1 interrupt_D5, 0xD5
DECLARE_INTR_PUSH1 interrupt_D6, 0xD6
DECLARE_INTR_PUSH1 interrupt_D7, 0xD7
DECLARE_INTR_PUSH1 interrupt_D8, 0xD8
DECLARE_INTR_PUSH1 interrupt_D9, 0xD9
DECLARE_INTR_PUSH1 interrupt_DA, 0xDA
DECLARE_INTR_PUSH1 interrupt_DB, 0xDB
DECLARE_INTR_PUSH1 interrupt_DC, 0xDC
DECLARE_INTR_PUSH1 interrupt_DD, 0xDD
DECLARE_INTR_PUSH1 interrupt_DE, 0xDE
DECLARE_INTR_PUSH1 interrupt_DF, 0xDF
DECLARE_INTR_PUSH1 interrupt_E0, 0xE0
DECLARE_INTR_PUSH1 interrupt_E1, 0xE1
DECLARE_INTR_PUSH1 interrupt_E2, 0xE2
DECLARE_INTR_PUSH1 interrupt_E3, 0xE3
DECLARE_INTR_PUSH1 interrupt_E4, 0xE4
DECLARE_INTR_PUSH1 interrupt_E5, 0xE5
DECLARE_INTR_PUSH1 interrupt_E6, 0xE6
DECLARE_INTR_PUSH1 interrupt_E7, 0xE7
DECLARE_INTR_PUSH1 interrupt_E8, 0xE8
DECLARE_INTR_PUSH1 interrupt_E9, 0xE9
DECLARE_INTR_PUSH1 interrupt_EA, 0xEA
DECLARE_INTR_PUSH1 interrupt_EB, 0xEB
DECLARE_INTR_PUSH1 interrupt_EC, 0xEC
DECLARE_INTR_PUSH1 interrupt_ED, 0xED
DECLARE_INTR_PUSH1 interrupt_EE, 0xEE
DECLARE_INTR_PUSH1 interrupt_EF, 0xEF
DECLARE_INTR_PUSH1 interrupt_F0, 0xF0
DECLARE_INTR_PUSH1 interrupt_F1, 0xF1
DECLARE_INTR_PUSH1 interrupt_F2, 0xF2
DECLARE_INTR_PUSH1 interrupt_F3, 0xF3
DECLARE_INTR_PUSH1 interrupt_F4, 0xF4
DECLARE_INTR_PUSH1 interrupt_F5, 0xF5
DECLARE_INTR_PUSH1 interrupt_F6, 0xF6
DECLARE_INTR_PUSH1 interrupt_F7, 0xF7
DECLARE_INTR_PUSH1 interrupt_F8, 0xF8
DECLARE_INTR_PUSH1 interrupt_F9, 0xF9
DECLARE_INTR_PUSH1 interrupt_FA, 0xFA
DECLARE_INTR_PUSH1 interrupt_FB, 0xFB
DECLARE_INTR_PUSH1 interrupt_FC, 0xFC
DECLARE_INTR_PUSH1 interrupt_FD, 0xFD
DECLARE_INTR_PUSH1 interrupt_FE, 0xFE
DECLARE_INTR_PUSH1 interrupt_FF, 0xFF
