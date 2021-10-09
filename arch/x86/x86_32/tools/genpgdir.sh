#!/bin/bash

numptab=4
if [[ ! -z "$1" ]]; then
    numptab="$1"
fi

echo "## generated: $(date -R)"
echo "## numptab: $((numptab + 1)) [default: 1]"
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
