.section .text

exception_generic:
    pushq %rax
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11

    /* arch/x86_64/sys/exceptions.c */
    movq -160(%rsp), %rsi
    movq -144(%rsp), %rdi
    call exception_handler

    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    popq %rax

    addq $16, %rsp

    iretq

#define DECLARE_EXCEPTION_PUSH1(label, num) \
    .global label;                          \
    label:                                  \
        pushq $num;                         \
        jmp exception_generic;

#define DECLARE_EXCEPTION_PUSH2(label, num) \
    .global label;                          \
    label:                                  \
        pushq $0;                           \
        pushq $num;                         \
        jmp exception_generic;

DECLARE_EXCEPTION_PUSH2(exception_00, 0x00) /* division by zero         */
DECLARE_EXCEPTION_PUSH2(exception_01, 0x01) /* debug exception          */
DECLARE_EXCEPTION_PUSH2(exception_02, 0x02) /* non-maskable interrupt   */
DECLARE_EXCEPTION_PUSH2(exception_03, 0x03) /* breakpoint               */
DECLARE_EXCEPTION_PUSH2(exception_04, 0x04) /* overflow                 */
DECLARE_EXCEPTION_PUSH2(exception_05, 0x05) /* bound range exceeded     */
DECLARE_EXCEPTION_PUSH2(exception_06, 0x06) /* invalid opcode           */
DECLARE_EXCEPTION_PUSH2(exception_07, 0x07) /* device not available     */
DECLARE_EXCEPTION_PUSH1(exception_08, 0x08) /* double fault             */
DECLARE_EXCEPTION_PUSH2(exception_09, 0x09) /* reserved                 */
DECLARE_EXCEPTION_PUSH1(exception_0A, 0x0A) /* invalid tss              */
DECLARE_EXCEPTION_PUSH1(exception_0B, 0x0B) /* segment not present      */
DECLARE_EXCEPTION_PUSH1(exception_0C, 0x0C) /* stack-segment fault      */
DECLARE_EXCEPTION_PUSH1(exception_0D, 0x0D) /* general protection fault */
DECLARE_EXCEPTION_PUSH1(exception_0E, 0x0E) /* page fault               */
DECLARE_EXCEPTION_PUSH2(exception_0F, 0x0F) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_10, 0x10) /* x87 FP exception         */
DECLARE_EXCEPTION_PUSH2(exception_11, 0x11) /* alignment check          */
DECLARE_EXCEPTION_PUSH2(exception_12, 0x12) /* machine check            */
DECLARE_EXCEPTION_PUSH2(exception_13, 0x13) /* SIMD FP exception        */
DECLARE_EXCEPTION_PUSH2(exception_14, 0x14) /* virtualization exception */
DECLARE_EXCEPTION_PUSH2(exception_15, 0x15) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_16, 0x16) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_17, 0x17) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_18, 0x18) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_19, 0x19) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_1A, 0x1A) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_1B, 0x1B) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_1C, 0x1C) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_1D, 0x1D) /* reserved                 */
DECLARE_EXCEPTION_PUSH2(exception_1E, 0x1E) /* security exception       */
DECLARE_EXCEPTION_PUSH2(exception_1F, 0x1F) /* reserved                 */
