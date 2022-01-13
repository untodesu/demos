entry x86.boot.stack_size unsigned_integer
    describe "Kernel stack size on boot"
    set_macro "BOOT_STACK_SIZE"
    set_value 16384
endentry

entry x86.boot.loader_title string
    describe "Bootloader entry title"
    set_macro "BOOTLOADER_TITLE"
    set_value "Demos/$target_arch"
endentry

check_f "$config_path/.limine.in.cfg"
check_f "$config_path/sysroot/boot/limine-cd.bin"
check_f "$config_path/sysroot/boot/limine-eltorito-efi.bin"
check_f "$config_path/sysroot/boot/limine.sys" # limine.sus
command -v "$tool_path/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"

cp -a "$config_path/sysroot/." "$sysr_path"
