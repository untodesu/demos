include ./config.0.mk
include ./config.1.mk

INTERNALCCFLAGS :=			\
	-std=gnu99				\
	-ffreestanding			\
	-fno-stack-protector	\
	-fno-pic -fpie			\
	-mno-80387				\
	-mno-mmx				\
	-mno-3dnow				\
	-mno-sse -mno-sse2		\
	-mno-red-zone

INTERNALCPFLAGS :=		\
	$(CONFIG_CPFLAGS)	\
	-nostdinc

INTERNALLDFLAGS	:=								\
	-fno-pic -fpie								\
	-Wl,-static,-pie,--no-dynamic-linker,-ztext	\
	-static-pie									\
	-nostdlib									\
	-T ./link.ld								\
	-z max-page-size=0x1000

CC := $(CONFIG_GCC)

CCFLAGS += $(INTERNALCCFLAGS)
CPFLAGS += $(INTERNALCPFLAGS)
LDFLAGS += $(INTERNALLDFLAGS)

SOURCES :=
CLEAN_LIST :=
TREE := .

define add_subdir
    TREE := $$(TREE)/$(1)

    sources_y :=
    clean_list_tree_y :=
	clean_list_root_y :=
    subdirs_y :=

    include $$(TREE)/Makefile

    SOURCES += $$(patsubst %,$$(TREE)/%,$$(sources_y))
    CLEAN_LIST += $$(patsubst %,$$(TREE)/%,$$(clean_list_tree_y))
	CLEAN_LIST += $$(clean_list_root_y)

    $$(foreach subdir,$$(subdirs_y),$$(eval $$(call add_subdir,$$(subdir))))

    TREE := $$(patsubst %/$(1),%,$$(TREE))
endef

BINARY := demos-$(CONFIG_VERSION).elf
CLEAN_LIST += $(BINARY)

$(eval $(call add_subdir,$(CONFIG_ARCHDIR)))
$(eval $(call add_subdir,lib))

OBJECTS := $(SOURCES:=.o)
CLEAN_LIST += $(OBJECTS)

.phony: all kernel clean soft_clean

all: kernel

kernel: $(BINARY)

clean: soft_clean
	@$(foreach item,$(CONFIG_CLEAN_LIST),echo "rm -f $(item)";rm -f $(item);)

# Soft clean means that we clean only object files
# and other things generated by MAKE and not configure script
soft_clean:
	@$(foreach item,$(CLEAN_LIST),echo "rm -f $(item)";rm -f $(item);)

$(BINARY): $(OBJECTS)
	$(CC) $(CCFLAGS) $(LDFLAGS) -static-libgcc -lgcc -o $(BINARY) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	$(CC) $(CCFLAGS) $(CPFLAGS) -c -o $@ $*
