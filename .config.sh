entry version string noedit
    describe "Kernel version"
    set_macro "VERSION"
    set_value "0.01"
endentry

entry git_rev hex_integer noedit
    describe "Latest git commit hash"
    set_macro "GIT_REV"
    set_value "$(git rev-parse --short=16 HEAD || echo 0)"
endentry

recurse drv
recurse kern
recurse $target_arch
