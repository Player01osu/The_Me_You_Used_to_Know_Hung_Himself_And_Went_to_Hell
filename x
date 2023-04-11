#!/bin/sh

case $1 in
    "x")
        ([ ! -e ./target ] && mkdir target && ./x r) || (([ -e ./target/main ] || ./x b) && ./target/main)
        ;;
    "b")
        make clean all
        ;;
    "r"|*)
        make clean all && ./target/main
esac
