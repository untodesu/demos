#!/bin/sh
shift $((OPTIND - 1))
echo "## generated: $(date -R)"
echo "## sources: $@"
for source in $@
do
    while IFS= read -r line
    do
        echo "${line%#*}" | sed -re "s/^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)\s*$/CONFIG_\\U\\1:=\\E\\2/;t;d"
    done < "$source"
done
exit 0
