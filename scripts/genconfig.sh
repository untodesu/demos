#!/bin/bash

while getopts "t:m:h" option
do
    if [[ "$option" = "t" ]]
    then
        target=$OPTARG
        continue
    fi

    if [[ "$option" = "m" ]]
    then
        macro=$OPTARG
        continue
    fi

    >&2 echo "usage: $0 [options] <source [sources...]>"
    >&2 echo "options:"
    >&2 echo "    -t <target> : set the target language"
    >&2 echo "    -m <macro>  : set the include guard macro"
    >&2 echo "    -h          : print this message and exit"
    exit 1
done

case "$target" in
    mk|make)
        target_comment="#"
        target_replace="CONFIG_\\U\\1:=\\E\\2"
        ;;
    
    c)
        target_comment="//"
        target_replace="#define CONFIG_\\U\\1 \\E\\2"
        if [[ -z "$macro" ]]
        then
            target_begin_1="#ifndef __GENCONFIG_H__"
            target_begin_2="#define __GENCONFIG_H__"
        else
            target_begin_1="#ifndef $macro"
            target_begin_2="#define $macro"
        fi
        target_end="#endif"
        ;;

    *)
        >&2 echo "$0: invalid target $target"
        exit 1
        ;;
esac

shift $(($OPTIND - 1))
sources=$@

echo "$target_comment"
echo "$target_comment generated: $(date)"
echo "$target_comment sources: $sources"
echo "$target_comment"

[[ ! -z "$target_begin_1" ]] && echo "$target_begin_1"
[[ ! -z "$target_begin_2" ]] && echo "$target_begin_2"

target_match="^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)\s*$"

for source in $sources
do
    if [[ -f "$source" ]]
    then
        while IFS= read -r line
        do
            echo "${line%#*}" | sed -re "s/$target_match/$target_replace/;t;d"
        done < "$source"
    fi
done

[[ ! -z "$target_end" ]] && echo "$target_end"

exit 0
