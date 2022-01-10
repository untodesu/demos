CCFLAGS += -fno-pic -mcmodel=kernel -mno-3dnow -mno-80387 -mno-mmx -mno-red-zone -mno-sse -mno-sse2
CPFLAGS += -D__X86_64__=1
LDFLAGS += -fno-pie -Wl,-static,--no-dynamic-linker,-ztext -z max-page-size=0x1000

ISOBIN := $(ARCHDIR)/root/boot/$(BINARY)
ISOCFG := $(ARCHDIR)/root/boot/limine.cfg
ISOSRC := $(ARCHDIR)/limine.in.cfg
ISOIMG := $(ROOTDIR)/demos-$(CONFIG_VERSION).$(ARCH).iso

clean_list_root_y += $(ISOBIN)
clean_list_root_y += $(ISOCFG)
clean_list_root_y += $(ISOIMG)

subdirs_y += boot
subdirs_y += kernel

.phony: iso qemu

iso: $(ISOIMG)

qemu: $(ISOIMG)
	qemu-system-x86_64 -cdrom $(ISOIMG)

$(ISOIMG): $(ISOBIN) $(ISOCFG)
	xorriso	-as mkisofs -b limine-cd.bin								\
			-no-emul-boot -boot-load-size 4 -boot-info-table			\
			--efi-boot limine-eltorito-efi.bin							\
			-efi-boot-part --efi-boot-image --protective-msdos-label	\
			$(ARCHDIR)/root -o $(ISOIMG)
	$(ARCHDIR)/tools/limine-install $(ISOIMG)

$(ISOBIN): $(BINARY)
	cp $(BINARY) $(ISOBIN)

$(ISOCFG): $(ISOSRC)
	BOOT_BINARY=$(BINARY)			\
	BOOT_ENTRY=$(CONFIG_BOOT_TITLE)	\
	envsubst < $(ISOSRC) > $(ISOCFG)
