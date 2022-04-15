include $(TREE)/.arch.mk

srcs_y += i8253.c
srcs_y += i8259.c
srcs_y += interrupt_trampoline.S
srcs_y += interrupts.c
srcs_y += segment.c

clns_y += interrupt_stubs.S
srcs_y += interrupt_stubs.S

$(TREE)/interrupt_stubs.S:
	$(TOOL_PATH)/x86_genintlist.sh > $@
