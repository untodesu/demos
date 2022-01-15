include $(TREE)/.arch.mk

srcs_y += entry.S
srcs_y += head.c
srcs_y += i8253.c
srcs_y += i8259.c
srcs_y += init.c
srcs_y += intr_trampoline.S
srcs_y += intr.c
srcs_y += pmm.c
srcs_y += seg.c
srcs_y += st2.c

clns_y += intr_stubs.S
srcs_y += intr_stubs.S

$(TREE)/intr_stubs.S:
	$(TOOL_PATH)/x86_genintlist.sh > $@
