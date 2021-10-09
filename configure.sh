#!/bin/sh

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

clean_list=
function add_clean {
    clean_list="$clean_list $1"
}

conf_list=
function add_conf {
    conf_list="$conf_list $1"
}

def_list=
function add_def {
    def_list="$def_list;CONFIG_$1:=$2"
}

arch=
if [ -z "$1" ]; then
    arch="x86"
    >&2 echo "argv[1] is not present, defaulting architecture to $arch"
else
    >&2 echo "Setting architecture to $1"
    arch="$1"
fi

rootdir="."
add_conf "$rootdir/kernel.conf"

archdir="$rootdir/arch/$arch"
archname="$arch"
archsubdir=
source "$archdir/configure.sh" || die "no configure.sh for $arch was found"

archroot="$archdir"
if [[ ! -z "$archsubdir" ]]; then
    archroot="$archdir/$archsubdir"
fi

sh "$rootdir/tools/confc.sh" $conf_list > "$rootdir/include/config.h"
sh "$rootdir/tools/confm.sh" $conf_list > "$rootdir/config.0.mk"

add_clean "$rootdir/include/config.h"
add_clean "$rootdir/config.0.mk"
add_clean "$rootdir/config.1.mk"
add_clean "$rootdir/config.sh"
add_clean "$rootdir/link.ld"

check_file "$archroot/gcc_list.txt"
check_file "$archroot/link.in.ld"

GCC="gcc"
while IFS= read -r line; do
    if [ -z "$line" ]; then continue; fi
    if command -v $line > /dev/null; then
        GCC=$line
        break
    fi
done < "$archroot/gcc_list.txt"
command -v $GCC > /dev/null || die "gcc not found"

$GCC -nostdinc -I "$rootdir/include" -I "$archdir/include" -I "$archroot/include" -E -xc -D__ASSEMBLER__=1 "$archroot/link.in.ld" | grep -v "^#" > "$rootdir/link.ld"

truncate -s 0 "$rootdir/config.1.mk"
echo "CONFIG_ARCH:=$arch"                               >> "$rootdir/config.1.mk"
echo "CONFIG_ARCHDIR:=$archdir"                         >> "$rootdir/config.1.mk"
echo "CONFIG_ARCHNAME:=$archname"                       >> "$rootdir/config.1.mk"
echo "CONFIG_ARCHSUBDIR:=$archsubdir"                   >> "$rootdir/config.1.mk"
echo "CONFIG_ARCHROOT:=$archroot"                       >> "$rootdir/config.1.mk"
echo "CONFIG_ROOTDIR:=$rootdir"                         >> "$rootdir/config.1.mk"
echo "CONFIG_GCC:=$GCC"                                 >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST :="                             >> "$rootdir/config.1.mk"
echo "CONFIG_CLEAN_LIST := $clean_list"                 >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS :="                                >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS += -I $rootdir/include"            >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS += -I $archdir/include"            >> "$rootdir/config.1.mk"
echo "CONFIG_CPFLAGS += -I $archroot/include"           >> "$rootdir/config.1.mk"
for it in $(echo $def_list | sed "s/;/ /g"); do
    echo "$it"                                          >> "$rootdir/config.1.mk"
done

exit 0
