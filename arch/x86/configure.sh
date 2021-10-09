if [[ -z "$X86_TARGET" ]]; then
    X86_TARGET="32"
    >&2 echo "Defaulting X86_TARGET to $X86_TARGET"
fi

check_dir "$archdir/x86_$X86_TARGET"
archname="x86_$X86_TARGET"
archsubdir="x86_$X86_TARGET"

add_conf "$archdir/arch.conf"
add_conf "$archdir/$archsubdir/arch.conf"

source "$archdir/$archsubdir/configure.sh" || die "no configure.sh for $archsubdir found"

check_file "$archdir/isoroot/limine-cd.bin"
check_file "$archdir/isoroot/limine-eltorito-efi.bin"
check_file "$archdir/isoroot/limine.sys" # limine.sus
command -v "$archdir/limine-install" > /dev/null || die "limine-install not found"
command -v xorriso > /dev/null || die "xorriso not found"
