sources_y += intr_trampoline.S
sources_y += intr_stubs.S
sources_y += intr.c
sources_y += segment.c

$(TREE)/intr_stubs.S:
	@$(ECHO) "generating $@"
	@./sh/geninterrupts.x86_64.sh > $@
clean_y += intr_stubs.S
