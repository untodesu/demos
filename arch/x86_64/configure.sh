check_file "$archdir/limine.in.cfg"
check_file "$archdir/root/limine-cd.bin"
check_file "$archdir/root/limine-eltorito-efi.bin"
check_file "$archdir/root/limine.sys" # limine.sus
command -v "$archdir/tools/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"
