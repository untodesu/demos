#!/bin/bash

echo ".section .text"
for i in $(seq 0 255); do
    echo "interrupt_$i:"

    # These interrupts generally "misbehave" by
    # pushing an error code to the stack before
    # passing control to the handler; this makes
    # it hard for us to have a unified structure
    # for the interrupt frame. So this dummy code
    # pushed to the stack essentially is a hack.
    if (( i != 8 && ( i < 10 || i > 14 ) && i != 21 )); then
        echo -e "pushq \$0"
    fi

    echo "pushq \$$i"
    echo "jmp __interrupt_trampoline"
done
echo

echo ".section .rodata"
echo ".global interrupt_stubs"
echo "interrupt_stubs:"
for i in $(seq 0 255); do
echo ".quad interrupt_$i"
done
