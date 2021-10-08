sh "$archdir/tools/genpgdir.sh" "$CONFIG_X86_INIT_PGDIR_SIZE" > "$archdir/boot/pgdir.S"
clean_file "$archdir/boot/pgdir.S"
