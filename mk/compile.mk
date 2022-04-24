# SPDX-License-Identifier: BSD-2-Clause
# Created: Sat Apr 23 2022 21:13:54

%.S.o %.o: %.S
	@$(ECHO) "assembling $<"
	@$(AS) $(ASFLAGS) $(ASFLAGS.$*.S) $(CPFLAGS) -c -o $@ $(realpath $<)
%.c.o %.o: %.c
	@$(ECHO) "compiling $<"
	@$(CC) $(CCFLAGS) $(CCFLAGS.$*.c) $(CPFLAGS) -c -o $@ $(realpath $<)
%.a:
	@$(ECHO) "generating $@"
	@$(AR) rs $@ $^ 2> /dev/null
%.ld: %.lds
	@$(ECHO) "preprocessing $<"
	@$(CC) $(CCFLAGS) $(CPFLAGS) -D__ASSEMBLER__=1 -E -xc $(realpath $<) | $(GREP) -v "^#" > $@ || $(TRUE)
