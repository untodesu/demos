include ./.config.0.mk
include ./.config.1.mk

include $(ROOT_PATH)/tools/scripts/make/common.mk
include $(ROOT_PATH)/tools/scripts/make/tools.arch.mk

ASFLAGS		+= -pipe -ffreestanding -O2
CFLAGS		+= -pipe -ffreestanding -O2
CPPFLAGS	+= -nostdinc -D__kernel__=1
CPPFLAGS	+= -I $(ROOT_PATH)/include
CPPFLAGS	+= -I $(ROOT_PATH)/sys/include
CPPFLAGS	+= -I $(ROOT_PATH)/sys/$(TARGET_ARCH)/include
LDFLAGS		+= -nostdlib -static -static-libgcc -lgcc -T link.ld

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

$(eval $(call recurse,sys))

OBJS := $(SRCS:=.o)
CLNS += $(OBJS)

all: $(KBIN)

kernel: $(KBIN)

clean: soft_clean
	$(MAKE) -C $(TOOL_PATH) clean
	@$(foreach it,$(HARD_CLNS),echo "$(RM) $(it)";$(RM) $(it);)
	$(RM) -r $(SYSR_PATH)

soft_clean:
	@$(foreach it,$(CLNS),echo "$(RM) $(it)";$(RM) $(it);)

$(KBIN): $(OBJS) link.ld
	$(LD) $(LDFLAGS) -o $(KBIN) $(OBJS)

.phony: $(PHONY_TARGETS)
