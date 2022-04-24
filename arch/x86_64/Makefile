subdirs_y += drivers
subdirs_y += sys

ISOBIN := demos.iso
CLEAN_FILES += $(ISOBIN)

./sysroot/boot/limine.cfg: $(TREE)/limine.in.cfg
	@$(ECHO) "generating $@"
	@BINARY=$(KBIN) $(ENVSUBST) < $(realpath $<) > $@

$(ISOBIN): ./host/limine-deploy sysroot $(KBIN) ./sysroot/boot/limine.cfg
	@$(ECHO) "generating $@"
	@xorriso	-as mkisofs -b boot/limine-cd.bin -no-emul-boot -boot-load-size 4	\
				-boot-info-table --efi-boot boot/limine-cd-efi.bin -efi-boot-part	\
				--efi-boot-image --protective-msdos-label ./sysroot -o $(ISOBIN)
	@./host/limine-deploy/limine-deploy $(ISOBIN)


PHONY_TARGETS += run_qemu
run_qemu: $(ISOBIN)
	@$(ECHO) "running QEMU"
	@qemu-system-x86_64 -cdrom $(ISOBIN)

PHONY_TARGETS += iso
iso: $(ISOBIN)
