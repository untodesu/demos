-include ./Makefile.config

VERSION := 0.01
VERSION_EXT :=

# todo: build the goddamn cross-compiler
ARCH ?= i686
TARGET ?= linux-gnu

CONFIG ?= ./kernel.conf
ARCH_CONFIG := ./arch/$(ARCH)/arch.conf

MKCONFIG := ./scripts/mkconfig.sh
GCC := $(ARCH)-$(TARGET)-gcc

CFLAGS := -std=gnu99 -ffreestanding -O3 -Wall -Wextra
CPPFLAGS := -nostdinc -I ./include/ -I ./arch/$(ARCH)/include/
LDFLAGS := -nostdlib -T ./ldscript.ld

SOURCES :=
CLEAN_LIST :=
TREE := .

# grob grob kladbishche pidor
LDFLAGS += -L /usr/lib/gcc-cross/i686-linux-gnu/7/

define add_subdir
        TREE := $$(TREE)/$(1)

        sources_y :=
        clean_list_y :=
        subdirs_y :=

        include $$(TREE)/Makefile

        SOURCES += $$(patsubst %,$$(TREE)/%,$$(sources_y))
        CLEAN_LIST += $$(patsubst %,$$(TREE)/%,$$(clean_list_y))

        $$(foreach subdir,$$(subdirs_y),$$(eval $$(call add_subdir,$$(subdir))))

        TREE := $$(patsubst %/$(1),%,$$(TREE))
endef

$(eval $(call add_subdir,arch/$(ARCH)))
$(eval $(call add_subdir,lib))

OBJECTS := $(SOURCES:=.o)
BINARY := vmdemos-$(ARCH)-$(VERSION)$(VERSION_EXT)

CLEAN_LIST += $(OBJECTS)
CLEAN_LIST += $(BINARY)

.phony: all configure build clean

all:

configure: $(CONFIG) $(ARCH_CONFIG)
	$(MKCONFIG) -t c $(CONFIG) $(ARCH_CONFIG) > ./include/demos/config.h
	$(MKCONFIG) -t mk $(CONFIG) $(ARCH_CONFIG) > ./Makefile.config
	$(GCC) $(CPPFLAGS) -E -xc -D__ASSEMBLER__ ./arch/$(ARCH)/ldscript.ldS | grep -v "^#" > ./ldscript.ld

CLEAN_LIST += ./include/demos/config.h
CLEAN_LIST += ./Makefile.config
CLEAN_LIST += ./ldscript.ld

build: $(BINARY)

clean:
	@$(foreach item,$(CLEAN_LIST),echo "rm -f $(item)";rm -f $(item);)

$(BINARY): $(OBJECTS)
	$(GCC) $(LDFLAGS) $(OBJECTS) -static-libgcc -lgcc  -o $(BINARY)

$(OBJECTS): $(SOURCES)
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $*
