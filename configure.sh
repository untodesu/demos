#!/bin/sh

die() {
    >&2 echo -e "\033[91m(!!!) fatal:\033[0m $@"
    exit 1
}

log() {
    >&2 echo -e "$@"
}

chk_dir() {
    if [ ! -d "$1" ]; then
        die "$1 no such directory"
    fi
}

chk_file() {
    if [ ! -f "$1" ]; then
        die "$1: no such directory"
    fi
}

arch=
if [ -z "$1" ]; then
    arch="x86_64"
    log "(!  ) argv[1] not present, defaulting arch=$arch"
else
    arch="$1"
    log "setting arch=$arch"
fi

host=
if [ -z "$2" ]; then
    host="linux_amd64"
    log "(!!!) argv[2] not present, defaulting host=$host"
else
    host="$2"
    chk_dir "$root_dir/$host"
    log "setting host=$host"
fi

bindir="./bin/$host"
archdir="./arch/$arch"
rootdir="."

chk_dir "$archdir"
chk_file "$archdir/gcc_list.txt"
chk_file "$archdir/link.in.ld"

"$bindir/defcon" -C "$rootdir/include/config.h" -M "$rootdir/config.0.mk" -c "$rootdir/kernel.conf" "$rootdir/defcon.ini" "$archdir/defcon.ini"

GCC_X="gcc"
while IFS= read -r line; do
    if [ -z "$line" ]; then continue; fi
    if command -v $line > /dev/null; then
        GCC_X=$line
        break
    fi
done < "$archdir/gcc_list.txt"
command -v $GCC_X > /dev/null || die "gcc not found"

truncate -s 0 $rootdir/config.1.mk
echo "ARCH:=$arch"                                  >> "$rootdir/config.1.mk"
echo "ARCHDIR:=$archdir"                            >> "$rootdir/config.1.mk"
echo "ROOTDIR:=$rootdir"                            >> "$rootdir/config.1.mk"
echo "GCC:=$GCC_X"                                  >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST :="                           >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/include/config.h" >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/config.0.mk"      >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/config.1.mk"      >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/link.ld"          >> "$rootdir/config.1.mk"
echo "CPFLAGS :="                                   >> "$rootdir/config.1.mk"
echo "CPFLAGS += -I $rootdir/include"               >> "$rootdir/config.1.mk"
echo "CPFLAGS += -I $archdir/include"               >> "$rootdir/config.1.mk"

$GCC_X -nostdinc -I "$rootdir/include" -I "$archdir/include" -E -xc -D__ASSEMBLER__=1 -D__kernel__=1 -D__demos__=1 "$archdir/link.in.ld" | grep -v "^#" > "$rootdir/link.ld"

if [ -f "$archdir/configure.sh" ]; then
    source "$archdir/configure.sh"
fi

exit 0
