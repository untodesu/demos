check_file "$archdir/limine.in.cfg"
check_file "$archdir/isoroot/limine-cd.bin"
check_file "$archdir/isoroot/limine-eltorito-efi.bin"
check_file "$archdir/isoroot/limine.sys" # limine.sus
command -v "$archdir/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"
