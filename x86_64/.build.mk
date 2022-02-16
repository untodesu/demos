include $(TREE)/.arch.mk

srcs_y += entry.S
srcs_y += head.c
srcs_y += i8253.c
srcs_y += i8259.c
srcs_y += init.c
srcs_y += interrupt_trampoline.S
srcs_y += interrupts.c
srcs_y += pmem.c
srcs_y += segment.c
srcs_y += st2.c

clns_y += interrupt_stubs.S
srcs_y += interrupt_stubs.S

$(TREE)/interrupt_stubs.S:
	$(TOOL_PATH)/x86_genintlist.sh > $@
