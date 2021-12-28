chk_file "$archdir/limine.in.cfg"
chk_file "$archdir/root/limine-cd.bin"
chk_file "$archdir/root/limine-eltorito-efi.bin"
chk_file "$archdir/root/limine.sys" # limine.sus
command -v "$bindir/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"
