#!/bin/bash

numptab=0

while getopts "n:h" option; do
    if [[ "$option" = 'n' ]]; then
        numptab=$((OPTARG - 1))
        continue
    fi

    >&2 echo "usage: $0 [options]"
    >&2 echo "options:"
    >&2 echo "    -n <numptab>  : set the number of page tables"
    >&2 echo "    -h            : print this message and exit"
    exit 1
done

echo "//"
echo "// generated: $(date)"
echo "// numptab: $((numptab + 1)) [default: 1]"
echo "//"
echo "#include <arch/paging.h>"
echo

echo ".section .data"
echo ".align PG_ALIGN"
echo

for i in $(seq 0 $numptab); do
    echo ".global pgtab_$i"
done
echo

echo ".set PGTAB_INDEX, 0"

for i in $(seq 0 $numptab); do
    echo
    echo "pgtab_$i:"
    echo "    .rept PG_COUNT"
    echo "    .long ((PGTAB_INDEX << PG_SHIFT) | PTE_PRESENT | PTE_READ_WRITE)"
    echo "    .set PGTAB_INDEX, (PGTAB_INDEX + 1)"
    echo "    .endr"
done

exit 0
