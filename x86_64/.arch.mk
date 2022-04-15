# Everything related to the target architecture
# is defined here. The .build.mk files are only
# for source files and source files generation.

X86_XFLAGS	:= -fno-pic -mcmodel=kernel -mno-3dnow -mno-80387 -mno-mmx -mno-red-zone -mno-sse -mno-sse2
ASFLAGS		+= $(X86_XFLAGS)
CFLAGS		+= $(X86_XFLAGS)
LDFLAGS		+= -fno-pie -Wl,-static,--no-dynamic-linker,-ztext -z max-page-size=0x1000
CPPFLAGS	+= -D__x86_64__=1 -D__X86_64__=1

ISOBIN := demos-$(CONFIG_VERSION).$(TARGET_ARCH).iso

clns_root_y += link.ld
clns_root_y += $(SYSR_PATH)/limine.cfg
clns_root_y += $(SYSR_PATH)/$(KBIN)
clns_root_y += $(ISOBIN)

link.ld: $(TREE)/.link.in.ld
	$(CC) $(CFLAGS) $(CPPFLAGS) -D__ASSEMBLER__=1 -E -xc $(realpath $<) | grep -v "^#" > $@ || true

$(SYSR_PATH)/boot/limine.cfg: $(TREE)/.limine.in.cfg
	BOOT_BINARY=$(KBIN)						\
	BOOT_ENTRY=$(CONFIG_BOOTLOADER_TITLE)	\
	envsubst < $(realpath $<) > $@

$(SYSR_PATH)/$(KBIN): $(KBIN)
	cp $< $@

$(ISOBIN): $(SYSR_PATH)/boot/limine.cfg $(SYSR_PATH)/$(KBIN)
	xorriso	-as mkisofs -b boot/limine-cd.bin							\
			-no-emul-boot -boot-load-size 4 -boot-info-table			\
			--efi-boot boot/limine-cd-efi.bin							\
			-efi-boot-part --efi-boot-image --protective-msdos-label	\
			$(SYSR_PATH) -o $(ISOBIN)
	$(TOOL_PATH)/limine-deploy $(ISOBIN)

PHONY_TARGETS += iso
iso: $(ISOBIN)

PHONY_TARGETS += qemu
qemu: $(ISOBIN)
	qemu-system-x86_64 -cdrom $(ISOBIN)
