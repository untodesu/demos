#!/bin/bash

function die {
    >&2 echo -e "\033[31;91;1m(!!!) \033[0m$@\033[0m"
    exit 1
}

function error {
    >&2 echo -e "\033[31;91;1m(!!!) \033[0m$@\033[0m"
}

function warn {
    >&2 echo -e "\033[33;93;1m(!! ) \033[0m$@\033[0m"
}

function note {
    >&2 echo -e "\033[36;96;1m(!  ) \033[0m$@\033[0m"
}

function info {
    >&2 echo -e "\033[37;97;1m(   ) \033[0m$@\033[0m"
}

function chk_dir {
    info "checking (dir ) $1"
    if [ ! -d "$1" ]; then
        die "$1 no such directory"
    fi
}

function chk_file {
    info "checking (file) $1"
    if [ ! -f "$1" ]; then
        die "$1: no such directory"
    fi
}

arch=
if [ -z "$1" ]; then
    arch="x86_64"
    warn "argv[1] not present, defaulting arch=$arch"
else
    arch="$1"
    info "setting arch=$arch"
fi

archdir="./arch/$arch"
rootdir="."

info "building necessary tools"
(cd "$rootdir/tools/defcon" && make defcon)

chk_dir "$archdir"
chk_file "$archdir/gcc_list.txt"
chk_file "$archdir/link.in.ld"

def_file="$rootdir/defcon.ini"
def_tree=()

truncate -s 0 "$def_file"

function def {
    case $1 in
        "walk")
            if [ -z $def_tree ]; then
                def_path="$2"
            else
                def_path="${def_tree[-1]}/$2"
            fi
            def_tree+=("$def_path")
            info "entering $def_path"
            if [ ! -f "$def_path/DefConfig" ]; then
                warn "walking through $def_path failed"
            else
                source "$def_path/DefConfig"
            fi
            unset def_tree[-1]
            ;;
        "begin")
            echo "[$2]" >> "$def_file"
            ;;
        "macro")
            echo "macro = $2" >> "$def_file"
            ;;
        "type")
            echo "type = $2" >> "$def_file"
            ;;
        "value")
            echo "value = $2" >> "$def_file"
            ;;
        "end")
            echo "" >> "$def_file"
            ;;
        *)
            warn "Unknown command: def $@"
            ;;
    esac
}

info "generating defcon.ini (DefConfig)"
def walk "."

info "generating config.h and config.0.mk"
"$rootdir/tools/defcon/defcon" -C "$rootdir/include/config.h" -M "$rootdir/config.0.mk" -c "$rootdir/kernel.conf" "$rootdir/defcon.ini"

GCC_X="gcc"
while IFS= read -r line; do
    if [ -z "$line" ]; then continue; fi
    if command -v $line > /dev/null; then
        GCC_X=$line
        break
    fi
done < "$archdir/gcc_list.txt"
command -v $GCC_X > /dev/null || die "gcc not found"
info "using gcc: $GCC_X"

info "generating config.1.mk"
truncate -s 0 $rootdir/config.1.mk
echo "ARCH:=$arch"                                  >> "$rootdir/config.1.mk"
echo "BINDIR:=$bindir"                              >> "$rootdir/config.1.mk"
echo "ARCHDIR:=$archdir"                            >> "$rootdir/config.1.mk"
echo "ROOTDIR:=$rootdir"                            >> "$rootdir/config.1.mk"
echo "GCC:=$GCC_X"                                  >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST :="                           >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/defcon.ini"       >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/include/config.h" >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/config.0.mk"      >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/config.1.mk"      >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/link.ld"          >> "$rootdir/config.1.mk"
echo "CPFLAGS :="                                   >> "$rootdir/config.1.mk"
echo "CPFLAGS += -I $rootdir/include"               >> "$rootdir/config.1.mk"
echo "CPFLAGS += -I $archdir/include"               >> "$rootdir/config.1.mk"

info "processing linker script"
$GCC_X -nostdinc -I "$rootdir/include" -I "$archdir/include" -E -xc -D__ASSEMBLER__=1 -D__kernel__=1 -D__delta__=1 "$archdir/link.in.ld" | grep -v "^#" > "$rootdir/link.ld"

exit 0
