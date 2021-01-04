#include <arch/address.h>
#include <arch/multiboot.h>
#include <arch/paging.h>
#include <arch/segment.h>
#include <demos/config.h>

#define MULTIBOOT_FLAGS     (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO)
#define MULTIBOOT_CHECKSUM  (0 - (MULTIBOOT_HEADER_MAGIC + MULTIBOOT_FLAGS))
#define BOOT_STACK_SIZE     (16384)
#define BOOT_STACK_ALIGN    (16)

.global _start
.type _start, @function

.section .multiboot
.align MULTIBOOT_HEADER_ALIGN
multiboot_header:
    .long MULTIBOOT_HEADER_MAGIC
    .long MULTIBOOT_FLAGS
    .long MULTIBOOT_CHECKSUM
    .long 0, 0, 0, 0, 0
    .long 0, 0, 0, 0

.section .bss, "aw", @nobits
.align BOOT_STACK_ALIGN
.skip BOOT_STACK_SIZE
boot_stack:

.section .rodata
boot_gdt:
    .quad GDT_BOOT_NULL
    .quad GDT_BOOT_CODE
    .quad GDT_BOOT_DATA
boot_gdt_descr:
    .word (boot_gdt_descr - boot_gdt - 1)
    .long boot_gdt

.section .data
.align PG_ALIGN
pgdir:
    .fill PG_COUNT, 4, 0

.section .text
_start:
    movl $V2P(boot_stack), %esp

    // The pre-generated page tables are PG_ALIGN-aligned;
    // this means we can safely drop the align math here.
    movl $V2P(pgtab_0), %eax
    orl $(PDE_PRESENT | PDE_READ_WRITE), %eax

    // offset = index * sizeof(int32) = index * 4
    movl $(V2P(pgdir) + PGDIR_INDEX(0) * 4), %ebx
    movl $(V2P(pgdir) + PGDIR_INDEX(CONFIG_MEM_BASE_ADDR) * 4), %edx

    movl $CONFIG_MEM_PAGE_TABS, %ecx
1:  movl %eax, (%ebx)
    movl %eax, (%edx)
    addl $(PG_COUNT * 4), %eax // pgtab_1 = pgtab_0 + (PG_COUNT * sizeof(int32))
    addl $4, %ebx
    addl $4, %edx
    loop 1b

    movl $V2P(pgdir), %eax
    movl %eax, %cr3

    movl %cr0, %eax
    orl $0x80000000, %eax
    movl %eax, %cr0

    lgdtl boot_gdt_descr

    jmpl $GDT_SELECTOR(0, 0, 1), $2f
2:  movw $GDT_SELECTOR(0, 0, 2), %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    addl $CONFIG_MEM_BASE_ADDR, %esp
    xorl %ebp, %ebp

    call arch_main

    cli
3:  hlt
    jmp 3b
