CCFLAGS +=			\
	-fno-pie -fPIC	\
	-mno-80387		\
	-mno-mmx		\
	-mno-3dnow		\
	-mno-sse -mno-sse2

CPFLAGS += -DX86_64

LDFLAGS +=									\
	-fno-pie -fPIC							\
	-Wl,-static,--no-dynamic-linker,-ztext	\
	-z max-page-size=0x1000

ISOBIN := $(CONFIG_ARCHROOT)/isoroot/boot/$(BINARY)
ISOCFG := $(CONFIG_ARCHROOT)/isoroot/boot/limine.cfg
ISOSRC := $(CONFIG_ARCHROOT)/limine.in.cfg
ISOIMG := $(CONFIG_ROOTDIR)/demos-$(CONFIG_VERSION)-$(CONFIG_ARCHNAME).iso

clean_list_root_y += $(ISOBIN)
clean_list_root_y += $(ISOCFG)
clean_list_root_y += $(ISOIMG)

subdirs_y += boot

.phony: iso

iso: $(ISOIMG)

$(ISOIMG): $(ISOBIN) $(ISOCFG)
	xorriso	-as mkisofs -b limine-cd.bin								\
			-no-emul-boot -boot-load-size 4 -boot-info-table			\
			--efi-boot limine-eltorito-efi.bin							\
			-efi-boot-part --efi-boot-image --protective-msdos-label	\
			$(CONFIG_ARCHROOT)/isoroot -o $(ISOIMG)
	$(CONFIG_ARCHROOT)/limine-install $(ISOIMG)

$(ISOBIN): $(BINARY)
	cp $(BINARY) $(ISOBIN)

$(ISOCFG): $(ISOSRC)
	BOOT_BINARY=$(BINARY)				\
	BOOT_ENTRY=$(CONFIG_X86_BOOT_TITLE)	\
	BOOT_VERSION=$(CONFIG_VERSION)		\
	envsubst < $(ISOSRC) > $(ISOCFG)
