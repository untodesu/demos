CCFLAGS += -fno-pic -mcmodel=kernel -mno-3dnow -mno-80387 -mno-mmx -mno-red-zone -mno-sse -mno-sse2
LDFLAGS += -fno-pie -Wl,-static,--no-dynamic-linker,-ztext -z max-page-size=0x1000

ISOBIN := $(ARCHDIR)/isoroot/boot/$(BINARY)
ISOCFG := $(ARCHDIR)/isoroot/boot/limine.cfg
ISOSRC := $(ARCHDIR)/limine.in.cfg
ISOIMG := $(ROOTDIR)/demos-$(VERSION).$(ARCH).iso

clean_list_root_y += $(ISOBIN)
clean_list_root_y += $(ISOCFG)
clean_list_root_y += $(ISOIMG)

subdirs_y += drivers
subdirs_y += init
subdirs_y += mm
subdirs_y += sys

.phony: iso

iso: $(ISOIMG)

$(ISOIMG): $(ISOBIN) $(ISOCFG)
	xorriso	-as mkisofs -b limine-cd.bin								\
			-no-emul-boot -boot-load-size 4 -boot-info-table			\
			--efi-boot limine-eltorito-efi.bin							\
			-efi-boot-part --efi-boot-image --protective-msdos-label	\
			$(ARCHDIR)/isoroot -o $(ISOIMG)
	$(ARCHDIR)/tools/limine-install $(ISOIMG)

$(ISOBIN): $(BINARY)
	cp $(BINARY) $(ISOBIN)

$(ISOCFG): $(ISOSRC)
	BOOT_BINARY=$(BINARY)				\
	BOOT_ENTRY=$(X86_BOOT_LOADER_TITLE)	\
	envsubst < $(ISOSRC) > $(ISOCFG)
