#!/bin/bash
# SPDX-License-Identifier: BSD-2-Clause

echo ".section .text"
for i in $(seq 0 255); do
    echo "interrupt_$i:"

    # These interrupts appear to "misbehave" and
    # have an error code pushed before we can do
    # anything. Hence others must do the same thing.
    (( i != 8 && ( i < 10 || i > 14 ) && i != 21 )) && \
        echo -e "pushq \$0"

    echo "pushq \$$i"
    echo "jmp __interrupt_trampoline"
done
echo

echo ".section .rodata"
echo ".global __intr_stubs"
echo "__intr_stubs:"
for i in $(seq 0 255); do
echo ".quad interrupt_$i"
done
