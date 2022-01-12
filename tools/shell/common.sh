#!/bin/bash

function die {
    >&2 echo -e "\033[31;91;1m(!!!) \033[0m$@\033[0m"
    exit 1
}

function error {
    >&2 echo -e "\033[31;91;1m(!!!) \033[0m$@\033[0m"
}

function warn {
    >&2 echo -e "\033[33;93;1m(!! ) \033[0m$@\033[0m"
}

function note {
    >&2 echo -e "\033[36;96;1m(!  ) \033[0m$@\033[0m"
}

function info {
    >&2 echo -e "\033[37;97;1m(   ) \033[0m$@\033[0m"
}

function check_d {
    info "checking (dir ) $1"
    if [ ! -d "$1" ]; then
        die "$1 no such directory"
    fi
}

function check_f {
    info "checking (file) $1"
    if [ ! -f "$1" ]; then
        die "$1: no such directory"
    fi
}
