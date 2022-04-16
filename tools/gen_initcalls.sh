#!/bin/bash

initcalls=$($1 -j ".discard.initcall.depend" -s "$2" | grep "^[ \t]*[0-9a-f]" | xxd -r | tr "\0" "\n" | tsort)

echo ".section .data"
echo ".global initcalls"
echo "initcalls:"
for i in $initcalls; do
    echo "    .quad __initcall_$i"
done
echo "    .quad 0"

exit 0
