check_file "$archdir/$archsubdir/grub.in.cfg"
command -v mformat > /dev/null || die "mformat not found"
command -v xorriso > /dev/null || die "xorriso not found"
command -v grub-mkrescue > /dev/null || die "grub-mkrescue not found"
add_clean "$archdir/$archsubdir/boot/pgdir.S"
sh "$archdir/$archsubdir/tools/genpgdir.sh" "$CONFIG_X86_INIT_PGDIR_SIZE" > "$archdir/$archsubdir/boot/pgdir.S"
