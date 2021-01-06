#!/bin/bash

# todo: build the goddamn cross-compiler
GCC_NAME="i686-linux-gnu-gcc"
GCC_LIBS="/usr/lib/gcc-cross/i686-linux-gnu/7/"

while getopts "Lh" option
do
    if [[ "$option" = "L" ]]
    then
        echo "$GCC_LIBS"
        exit 0
    fi

    >&2 echo "usage: $0 [options]"
    >&2 echo "options:"
    >&2 echo "    -L : print the library path and exit"
    >&2 echo "    -h : print this message and exit"
    exit 1
done

echo "$GCC_NAME"
exit 0
