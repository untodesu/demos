include $(TREE)/.arch.mk

srcs_y += i8253.c
srcs_y += i8259.c
srcs_y += intr_trampoline.S
srcs_y += intr.c
srcs_y += segment.c

clns_y += intr_stubs.S
srcs_y += intr_stubs.S

$(TREE)/intr_stubs.S:
	$(TOOL_PATH)/x86_gen_intr_stubs.sh > $@
