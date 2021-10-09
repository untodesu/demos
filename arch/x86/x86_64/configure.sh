check_file "$archdir/$archsubdir/isoroot/limine-cd.bin"
check_file "$archdir/$archsubdir/isoroot/limine-eltorito-efi.bin"
check_file "$archdir/$archsubdir/isoroot/limine.sys" # limine.sus
command -v "$archdir/$archsubdir/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"
