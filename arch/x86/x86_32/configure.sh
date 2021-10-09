add_def X86_BOOT_PROTOCOL multiboot
add_clean "$archdir/$archsubdir/boot/pgdir.S"
sh "$archdir/$archsubdir/tools/genpgdir.sh" "$CONFIG_X86_INIT_PGDIR_SIZE" > "$archdir/$archsubdir/boot/pgdir.S"
