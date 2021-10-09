ISOBIN := $(CONFIG_ARCHDIR)/isoroot/boot/$(BINARY)
ISOCFG := $(CONFIG_ARCHDIR)/isoroot/boot/grub/grub.cfg
ISOSRC := $(CONFIG_ARCHDIR)/grub.in.cfg
ISOIMG := $(CONFIG_ROOTDIR)/demos-$(CONFIG_VERSION)-$(CONFIG_ARCH).iso

clean_list_root_y += $(ISOBIN)
clean_list_root_y += $(ISOCFG)
clean_list_root_y += $(ISOIMG)

subdirs_y += boot
subdirs_y += kernel

.phony: iso

iso: $(ISOIMG)

$(ISOIMG): $(ISOBIN) $(ISOCFG)
	grub-mkrescue -o "$(ISOIMG)" "$(CONFIG_ARCHDIR)/isoroot"

$(ISOBIN): $(BINARY)
	cp $(BINARY) $(ISOBIN)

$(ISOCFG): $(ISOSRC)
	BOOT_BINARY=$(BINARY)				\
	BOOT_ENTRY=$(CONFIG_X86_BOOT_TITLE)	\
	BOOT_VERSION=$(CONFIG_VERSION)		\
	envsubst < $(ISOSRC) > $(ISOCFG)
