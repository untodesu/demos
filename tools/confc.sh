#!/bin/sh
shift $((OPTIND - 1))
echo "/* generated: $(date -R)"
echo " * sources: $@ */"
echo "#ifndef CONFIG_H"
echo "#define CONFIG_H 1"
for source in $@
do
    while IFS= read -r line
    do
        echo "${line%#*}" | sed -re "s/^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)\s*$/#define CONFIG_\\U\\1 \\E\\2/;t;d"
    done < "$source"
done
echo "#endif"
exit 0
