include ./config.0.mk
include ./config.1.mk

include $(ROOT_PATH)/tools/make/common.mk
include $(ROOT_PATH)/tools/make/tools.arch.mk

ASFLAGS		+= -pipe -ffreestanding -O2
CFLAGS		+= -pipe -ffreestanding -O2
CPPFLAGS	+= -nostdinc -D__kernel__=1
CPPFLAGS	+= -I $(ROOT_PATH)/include
CPPFLAGS	+= -I $(ROOT_PATH)/sys/include
CPPFLAGS	+= -I $(ROOT_PATH)/sys/$(TARGET_ARCH)/include
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
KBIN_INITCALL_C := vmdemos_initcall.c
KBIN_INITCALL_O := $(KBIN_INITCALL_C:=.o)
CLNS += $(KBIN_NOINIT) $(KBIN_INITCALL_C) $(KBIN_INITCALL_O)

$(eval $(call recurse,sys))

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

$(KBIN): $(KBIN_NOINIT) $(KBIN_INITCALL_O) link.ld
	$(LD) $(LDFLAGS) -T link.ld -o $@ $(KBIN_NOINIT) $(KBIN_INITCALL_O)
	$(RM) $(KBIN_INITCALL_O)

$(KBIN_NOINIT): $(OBJS) link.ld
	$(LD) $(LDFLAGS) -T link.ld -r -o $@ $(OBJS)

$(KBIN_INITCALL_C):
	$(TOOL_PATH)/geninitcalls.sh $(ROOT_PATH) $(TARGET_PREFIX) $(KBIN_NOINIT) > $@

.phony: $(PHONY_TARGETS)
