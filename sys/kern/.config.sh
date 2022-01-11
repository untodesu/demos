entry kern.klog.entry_size unsigned_integer
    describe "KLog message size limit"
    set_macro "KLOG_ENTRY_SIZE"
    set_value 1024
endentry

entry kern.klog.entry_count unsigned_integer
    describe "KLog ring buffer size"
    set_macro "KLOG_ENTRY_COUNT"
    set_value 128
endentry
