#!/bin/sh

# apply tools so we can call config generators from
# outer space a.k.a. arch sub-directiories
PATH=$PATH:"$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/tools"
PROG="$0"

function die {
    >&2 echo "$PROG: fatal: $@"
    exit 1
}

function check_dir {
    if [ ! -d "$1" ]; then
        die "directory $1 doesn't exist"
    fi
}

function check_file {
    if [ ! -f "$1" ]; then
        die "file $1 doesn't exist"
    fi
}

arch=
if [ -z "$1" ]; then
    arch="x86_64"
    >&2 echo "argv[1] not specified, defaulting architecture to $arch"
else
    arch="$1"
    >&2 echo "Setting architecture to $arch"
fi

archdir="./arch/$arch"
rootdir="."

check_dir "$archdir"
check_file "$archdir/gcc_list.txt"
check_file "$archdir/link.in.ld"

"$rootdir/tools/defcon" -C "$rootdir/include/config.h"  -c "$rootdir/kernel.conf" "$rootdir/defcon.ini" "$archdir/defcon.ini"
"$rootdir/tools/defcon" -M "$rootdir/config.0.mk"       -c "$rootdir/kernel.conf" "$rootdir/defcon.ini" "$archdir/defcon.ini"

GCC="gcc"
while IFS= read -r line; do
    if [ -z "$line" ]; then continue; fi
    if command -v $line > /dev/null; then
        GCC=$line
        break
    fi
done < "$archdir/gcc_list.txt"
command -v $GCC > /dev/null || die "gcc not found"

truncate -s 0 $rootdir/config.1.mk
echo "ARCH:=$arch"                                  >> "$rootdir/config.1.mk"
echo "ARCHDIR:=$archdir"                            >> "$rootdir/config.1.mk"
echo "ROOTDIR:=$rootdir"                            >> "$rootdir/config.1.mk"
echo "GCC:=$GCC"                                    >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST :="                           >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/include/config.h" >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/config.0.mk"      >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/config.1.mk"      >> "$rootdir/config.1.mk"
echo "HARD_CLEAN_LIST += $rootdir/link.ld"          >> "$rootdir/config.1.mk"
echo "CPFLAGS :="                                   >> "$rootdir/config.1.mk"
echo "CPFLAGS += -I $rootdir/include"               >> "$rootdir/config.1.mk"
echo "CPFLAGS += -I $archdir/include"               >> "$rootdir/config.1.mk"

$GCC -nostdinc -I "$rootdir/include" -I "$archdir/include" -E -xc -D__ASSEMBLER__=1 "$archdir/link.in.ld" | grep -v "^#" > "$rootdir/link.ld"

if [ -f "$archdir/configure.sh" ]; then
    source "$archdir/configure.sh"
fi

exit 0
