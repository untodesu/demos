entry kern.printk.message_size unsigned_integer
    describe "printk message size limit"
    set_macro "PRINTK_MESSAGE_SIZE"
    set_value 1024
endentry

entry kern.printk.buffer_length unsigned int
    describe "printk message buffer length"
    set_macro "PRINTK_BUFFER_LENGTH"
    set_value 128
endentry
