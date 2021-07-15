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
    >&2 echo "argv[1] not specified, defaulting target architecture to x86_64"
    arch="x86_64"
else
    >&2 echo "Setting target architecture to $1"
    arch="$1"
fi

archdir="./arch/$arch"
rootdir="."

check_dir "$archdir"
check_file "$archdir/arch.conf"
check_file "$archdir/gcc_list.txt"
check_file "$archdir/link.in.ld"

sh "$rootdir/tools/confc.sh" "$rootdir/kernel.conf" "$archdir/arch.conf" > "$rootdir/include/config.h"
sh "$rootdir/tools/confm.sh" "$rootdir/kernel.conf" "$archdir/arch.conf" > "$rootdir/config.0.mk"

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
echo "CONFIG_ARCH:=$arch"                               >> "$rootdir/config.1.mk"
echo "CONFIG_ARCHDIR:=$archdir"                         >> "$rootdir/config.1.mk"
echo "CONFIG_ROOTDIR:=$rootdir"                         >> "$rootdir/config.1.mk"
echo "CONFIG_GCC:=$GCC"                                 >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST :="                             >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST += $rootdir/include/config.h"   >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST += $rootdir/config.0.mk"        >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST += $rootdir/config.1.mk"        >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST += $rootdir/link.ld"            >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS :="                                >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS += -I $rootdir/include"            >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS += -I $archdir/include"            >> "$rootdir/config.1.mk"

$GCC -nostdinc -I "$rootdir/include" -I "$archdir/include" -E -xc -D__ASSEMBLER__=1 "$archdir/link.in.ld" | grep -v "^#" > "$rootdir/link.ld"

if [ -f "$archdir/configure.sh" ]; then
    source "$archdir/configure.sh"
fi

exit 0
