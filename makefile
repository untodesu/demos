include ./config.0.mk
include ./config.1.mk

include $(ROOT_PATH)/tools/make/common.mk
include $(ROOT_PATH)/tools/make/tools.arch.mk

ASFLAGS		+= -pipe -ffreestanding -O2
CFLAGS		+= -pipe -ffreestanding -O2
CPPFLAGS	+= -nostdinc -D__kernel__=1
CPPFLAGS	+= -I $(ROOT_PATH)/include
CPPFLAGS	+= -I $(ROOT_PATH)/$(TARGET_ARCH)/include
LDFLAGS		+= -nostdlib -static -static-libgcc -lgcc

CLNS :=
SRCS :=
TREE := .

PHONY_TARGETS :=

define recurse
TREE := $$(TREE)/$(1)

clns_y :=
srcs_y :=
tree_y :=
clns_root_y :=
srcs_root_y :=

include $$(TREE)/.build.mk

CLNS += $$(patsubst %,$$(TREE)/%,$$(clns_y)) $$(clns_root_y)
SRCS += $$(patsubst %,$$(TREE)/%,$$(srcs_y)) $$(srcs_root_y)

$$(foreach it,$$(tree_y),$$(eval $$(call recurse,$$(it))))

TREE := $$(patsubst %/$(1),%,$$(TREE))
endef

KBIN := vmdemos
CLNS += $(KBIN)

KBIN_NOINIT := vmdemos_noinit.o
KBIN_INITCALLS_S := vmdemos_initcalls.S
KBIN_INITCALLS_O := $(KBIN_INITCALLS_S:=.o)
CLNS += $(KBIN_NOINIT) $(KBIN_INITCALLS_S) $(KBIN_INITCALLS_O)

$(eval $(call recurse,drv))
$(eval $(call recurse,kern))
$(eval $(call recurse,$(TARGET_ARCH)))

OBJS := $(SRCS:=.o)
CLNS += $(OBJS)

PHONY_TARGETS += all
all: $(KBIN)

PHONY_TARGETS += kernel
kernel: $(KBIN)

PHONY_TARGETS += clean
clean: soft_clean
	$(MAKE) -C $(TOOL_PATH) clean
	@$(foreach it,$(HARD_CLNS),echo "$(RM) $(it)";$(RM) $(it);)
	$(RM) -r $(SYSR_PATH)

PHONY_TARGETS += soft_clean
soft_clean:
	@$(foreach it,$(CLNS),echo "$(RM) $(it)";$(RM) $(it);)

$(KBIN): $(KBIN_NOINIT) $(KBIN_INITCALLS_O) link.ld
	$(LD) $(LDFLAGS) -T link.ld -o $@ $(KBIN_NOINIT) $(KBIN_INITCALLS_O)
	$(RM) $(KBIN_INITCALLS_S) $(KBIN_INITCALLS_O)

$(KBIN_NOINIT): $(OBJS) link.ld
	$(LD) $(LDFLAGS) -T link.ld -r -o $@ $(OBJS)

$(KBIN_INITCALLS_S):
	$(TOOL_PATH)/geninitcalls.sh $(OBJDUMP) $(KBIN_NOINIT) > $@

.phony: $(PHONY_TARGETS)
