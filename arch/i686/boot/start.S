#include <arch/multiboot.h>
#include <arch/paging.h>
#include <arch/segment.h>
#include <arch/vaddr.h>
#include <config.h>

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
    .quad SEG_BOOT_NULL
    .quad SEG_BOOT_CODE
    .quad SEG_BOOT_DATA
boot_gdt_descr:
    .word (boot_gdt_descr - boot_gdt - 1)
    .long boot_gdt

.section .data
.align PG_ALIGN
pgdir:
    .fill PG_COUNT, 4, 0

.section .text
_start:
    movl $virt_to_phys(boot_stack), %esp

    /* genpgdir actually produces page tables that are
     * going to be put in the initial page directory. */
    movl $virt_to_phys(pgtab_0), %eax
    orl $(PDE_PRESENT | PDE_READ_WRITE), %eax

    movl $(virt_to_phys(pgdir) + PGDIR_INDEX(0) * 4), %ebx
    movl $(virt_to_phys(pgdir) + PGDIR_INDEX(CONFIG_X86_BASE_ADDR) * 4), %edx

    movl $CONFIG_X86_INIT_PGDIR_SIZE, %ecx
1:  movl %eax, (%ebx)
    movl %eax, (%edx)
    addl $(PG_COUNT * 4), %eax
    addl $4, %ebx
    addl $4, %edx
    loop 1b

    /* UNDONE: should this page directory be scrapped
     * after some time in the virtual space or it's okay
     * to reuse it after all? If it is, it should probably
     * be marked as .global like the ELF entrypoint is. */
    movl $virt_to_phys(pgdir), %eax
    movl %eax, %cr3

    movl %cr0, %eax
    orl $0x80000000, %eax
    movl %eax, %cr0

    lgdtl boot_gdt_descr

    jmpl $SEG_SELECTOR(0, 0, 1), $2f
2:  movw $SEG_SELECTOR(0, 0, 2), %ax

    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    addl $CONFIG_X86_BASE_ADDR, %esp
    xorl %ebp, %ebp

    call arch_init

    cli
3:  hlt
    jmp 3b
