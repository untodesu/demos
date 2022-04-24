# SPDX-License-Identifier: BSD-2-Clause
# Created: Sat Apr 23 2022 21:18:52

# These are not required
-include ./config.$(ARCH).mk
-include ./config.mk

# Make sure it's defined
ARCH ?= x86_64
KERNEL_FILE ?= kernel.elf

include ./mk/$(ARCH)/flags.mk
include ./mk/$(ARCH)/tools.mk

include ./mk/compile.mk
include ./mk/flags.mk
include ./mk/tools.mk

PHONY_TARGETS :=

ASFLAGS	+= -O2 -Wall -Wextra -Werror -pedantic
CCFLAGS	+= -Wall -Wextra -Werror -pedantic -std=gnu99
CPFLAGS += -I./arch/$(ARCH)/include
CPFLAGS += -I./include
CPFLAGS += -D__DEMOS__=1
CPFLAGS += -D__demos__=1

CLEAN_FILES :=
OBJECTS :=
SOURCES :=
TREE := .

define recurse
    TREE := $$(TREE)/$(1)

	clean_y :=
    objects_y :=
    sources_y :=
	clean_root_y :=
    objects_root_y :=
    sources_root_y :=
    subdirs_y :=

    include $$(TREE)/Makefile

	CLEAN_FILES += $$(patsubst %,$$(TREE)/%,$$(clean_y)) $$(clean_root_y)
    OBJECTS += $$(patsubst %,$$(TREE)/%,$$(objects_y)) $$(objects_root_y)
    SOURCES += $$(patsubst %,$$(TREE)/%,$$(sources_y)) $$(sources_root_y)

    $$(foreach it,$$(subdirs_y),$$(eval $$(call recurse,$$(it))))

    TREE := $$(patsubst %/$(1),%,$$(TREE))
endef

# Gather sources recursively
$(eval $(call recurse,arch/$(ARCH)))
$(eval $(call recurse,drivers))
$(eval $(call recurse,lib))
$(eval $(call recurse,sys))

OBJECTS += $(SOURCES:=.o)

KBIN := kernel.elf
KBIN_NOINIT := kernel_noinit
KBIN_INITCALLS_S := kernel_initcalls.S
KBIN_INITCALLS_O := kernel_initcalls.o
KBIN_LDSCRIPT := ./lds/$(ARCH)/sys.ld

CLEAN_FILES += $(OBJECTS)
CLEAN_FILES += $(KBIN) $(KBIN_NOINIT)
CLEAN_FILES += $(KBIN_INITCALLS_S) $(KBIN_INITCALLS_O)
CLEAN_FILES += $(KBIN_LDSCRIPT)

PHONY_TARGETS += clean
clean:
	@$(RM) -v $(CLEAN_FILES)
	@$(RM) -rv ./sysroot

PHONY_TARGETS += sysroot
sysroot: $(KBIN)
	@$(ECHO) "generating sysroot"
	@$(MKDIR) -p ./sysroot
	@$(MKDIR) -p ./sysroot/boot
	@$(CP) -a ./arch/$(ARCH)/sysroot ./
	@$(CP) $(KBIN) ./sysroot/$(KBIN)

PHONY_TARGETS += all
all: sysroot

# Build the kernel with initcalls
$(KBIN): $(KBIN_NOINIT) $(KBIN_INITCALLS_O) $(KBIN_LDSCRIPT)
	@$(ECHO) "linking $@"
	@$(LD) $(LDFLAGS) -T $(KBIN_LDSCRIPT) -o $@ $(KBIN_NOINIT) $(KBIN_INITCALLS_O)
	@$(RM) -v $(KBIN_INITCALLS_S) $(KBIN_INITCALLS_O)

# Build the kernel without initcalls
$(KBIN_NOINIT): $(OBJECTS)
	@$(ECHO) "linking $@"
	@$(LD) $(LDFLAGS) -r -o $@ $(OBJECTS)

# Generate an initcall list
$(KBIN_INITCALLS_S):
	@$(ECHO) "generating $@"
	@./sh/geninitcalls.sh $(OBJDUMP) $(KBIN_NOINIT) > $@

# Setup phony targets
.phony: $(PHONY_TARGETS)
