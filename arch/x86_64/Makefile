CCFLAGS += -fno-pie -fPIC -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2
LDFLAGS += -fno-pie -fPIC -Wl,-static,--no-dynamic-linker,-ztext -z max-page-size=0x1000

ISOBIN := $(CONFIG_ARCHDIR)/isoroot/boot/$(BINARY)
ISOCFG := $(CONFIG_ARCHDIR)/isoroot/boot/limine.cfg
ISOSRC := $(CONFIG_ARCHDIR)/limine.in.cfg
ISOIMG := $(CONFIG_ROOTDIR)/demos-$(CONFIG_VERSION).$(CONFIG_ARCH).iso

clean_list_root_y += $(ISOBIN)
clean_list_root_y += $(ISOCFG)
clean_list_root_y += $(ISOIMG)

subdirs_y += drivers
subdirs_y += init
subdirs_y += kernel

.phony: iso

iso: $(ISOIMG)

$(ISOIMG): $(ISOBIN) $(ISOCFG)
	xorriso	-as mkisofs -b limine-cd.bin								\
			-no-emul-boot -boot-load-size 4 -boot-info-table			\
			--efi-boot limine-eltorito-efi.bin							\
			-efi-boot-part --efi-boot-image --protective-msdos-label	\
			$(CONFIG_ARCHDIR)/isoroot -o $(ISOIMG)
	$(CONFIG_ARCHDIR)/limine-install $(ISOIMG)

$(ISOBIN): $(BINARY)
	cp $(BINARY) $(ISOBIN)

$(ISOCFG): $(ISOSRC)
	BOOT_BINARY=$(BINARY)				\
	BOOT_ENTRY=$(CONFIG_X86_BOOT_TITLE)	\
	envsubst < $(ISOSRC) > $(ISOCFG)
