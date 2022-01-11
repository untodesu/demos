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

function check_d {
    info "checking (dir ) $1"
    if [ ! -d "$1" ]; then
        die "$1 no such directory"
    fi
}

function check_f {
    info "checking (file) $1"
    if [ ! -f "$1" ]; then
        die "$1: no such directory"
    fi
}

function _usage {
    error "usage: configure.sh [options]"
    error "options:"
    error " -a <arch>   : set the target arhitecture"
    error " -h          : print this message and exit"
}

target_arch=
while getopts "a:h" opt; do
    case "$opt" in
        "a")    target_arch="$OPTARG"   ;;
        "h")    _usage; exit 0          ;;
        *)      _usage; exit 1          ;;
    esac
done

if [ -z "$target_arch" ]; then
    target_arch="x86_64"
    warn "target_arch not set, defaulting to $target_arch"
fi

target_gcc_exec=
target_prefix=

target_prefixes=("unknown-elf" "unknown" "demos-elf" "demos")
for pfx in $target_prefixes; do
    gcc_exec="$target_arch-$pfx-gcc"
    if command -v $gcc_exec > /dev/null; then
        target_gcc_exec="$gcc_exec"
        target_prefix="$pfx"
        break
    fi
done
command -v $target_gcc_exec > /dev/null || die "gcc not found"
info "using $target_gcc_exec"

root_path="."
tool_path="./tools"
sysr_path="./sysroot"

mkdir -p "$sysr_path"

info "building tools"
make install -C "$tool_path"
check_f "$tool_path/genconfig"

config_ecur="null"
config_outf="$root_path/.config.deffile"
config_tree=()

truncate -s 0 "$config_outf"

function recurse {
    if [ -z "$config_tree" ]; then
        config_path="$1"
    else
        config_path="${config_tree[-1]}/$1"
    fi
    info "entering $config_path"
    config_tree+=("$config_path")
    _config_sh="$config_path/.config.sh"
    if [ -f "$_config_sh" ]; then
        source "$_config_sh"
    else
        warn "walking through $config_path failed"
    fi
    unset config_tree[-1]
}

function entry {
    config_ecur="$1"
    echo "\$entry\$$1\$$2\$" >> "$config_outf"
    if [ "$3" == "noedit" ]; then
        echo "\$noedit\$$1\$" >> "$config_outf"
    fi
}

function endentry {
    config_ecur=""
}

function describe {
    if [ ! -z "$config_ecur" ]; then
        echo "\$describe\$$config_ecur\$$@\$" >> "$config_outf"
    else
        warn "calling \"$0\" without active entry"
    fi
}

function set_macro {
    if [ ! -z "$config_ecur" ]; then
        echo "\$set_macro\$$config_ecur\$$1\$" >> "$config_outf"
    else
        warn "calling \"$0\" without active entry"
    fi
}

function set_value {
    if [ ! -z "$config_ecur" ]; then
        echo "\$set_value\$$config_ecur\$$@\$" >> "$config_outf"
    else
        warn "calling \"$0\" without active entry"
    fi
}

info "generating $config_outf"
recurse "."

config_chead="$root_path/include/config.h"
config_make0="$root_path/.config.0.mk"
config_make1="$root_path/.config.1.mk"

info "generating $config_chead"
info "generating $config_make0"
"$tool_path/genconfig" -C "$config_chead" -M "$config_make0" "$root_path/demos.conf" "$config_outf"

info "generating $config_make1"
truncate -s 0 "$config_make1"
echo "TARGET_ARCH := $target_arch"          >> "$config_make1"
echo "TARGET_GCC_EXEC := $target_gcc_exec"  >> "$config_make1"
echo "TARGET_PREFIX := $target_prefix"      >> "$config_make1"
echo "ROOT_PATH := $root_path"              >> "$config_make1"
echo "TOOL_PATH := $tool_path"              >> "$config_make1"
echo "SYSR_PATH := $sysr_path"              >> "$config_make1"
echo "HARD_CLNS :="                         >> "$config_make1"
echo "HARD_CLNS += $config_outf"            >> "$config_make1"
echo "HARD_CLNS += $config_chead"           >> "$config_make1"
echo "HARD_CLNS += $config_make0"           >> "$config_make1"
echo "HARD_CLNS += $config_make1"           >> "$config_make1"
echo "CPPFLAGS += -D__demos__=1"            >> "$config_make1"

check_f "$config_chead"
check_f "$config_make0"
check_f "$config_make1"

error "done"
exit 0
