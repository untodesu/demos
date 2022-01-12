#!/bin/bash

target_prefix="$2"
alias objdump="$target_prefix-objdump"

source "$1/tools/shell/common.sh" || exit 1
command -v objdump > /dev/null || die "objdump not found"

initcall_list=$(objdump -j ".discard.initcalls.dep" -s "$3" | grep "^[ \t]*[0-9a-f]" | xxd -r | tr "\0" "\n" | tsort)

echo "#include <sys/init.h>"
echo "#include <stddef.h>"
for i in $initcall_list; do echo "extern int __initcall_$i(void);"; done
echo "const initcall_t initcalls[] = {"
for i in $initcall_list; do echo "&__initcall_$i,"; done
echo "NULL"
echo "};"

exit 0
"""
