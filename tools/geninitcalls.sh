#!/bin/bash

source "$1/tools/shell/common.sh" || exit 1
command -v $2 > /dev/null || die "objdump not found"

initcalls=$($2 -j ".discard.initcall.depend" -s "$3" | grep "^[ \t]*[0-9a-f]" | xxd -r | tr "\0" "\n" | tsort)

echo ".section .data"
echo ".global initcalls"
echo "initcalls:"
for i in $initcalls; do
    echo "    .quad __initcall_$i"
done
echo "    .quad 0"

exit 0
