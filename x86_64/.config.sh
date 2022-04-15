entry x86.bootloader_title string
    describe "Bootloader entry title"
    set_macro "BOOTLOADER_TITLE"
    set_value "Demos/$target_arch"
endentry

check_f "$tool_path/x86_genintlist.sh"

check_f "$config_path/.limine.in.cfg"
check_f "$config_path/sysroot/boot/limine-cd.bin"
check_f "$config_path/sysroot/boot/limine-eltorito-efi.bin"
check_f "$config_path/sysroot/boot/limine.sys" # limine.sus
command -v "$tool_path/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"

cp -a "$config_path/sysroot/." "$sysr_path"
