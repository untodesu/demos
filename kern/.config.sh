entry kern.boot.stack_size unsigned_integer
    describe "Kernel stack size on boot"
    set_macro "BOOT_STACK_SIZE"
    set_value 16384
endentry

entry kern.printk.message_size unsigned_integer
    describe "printk message size limit"
    set_macro "PRINTK_MSG_SIZE"
    set_value 1024
endentry

entry kern.printk.buffer_length unsigned_integer
    describe "printk message buffer length"
    set_macro "PRINTK_BUFFER_LENGTH"
    set_value 128
endentry

recurse acpi
