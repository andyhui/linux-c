#!/bin/sh
if [ -f 'cscope.*' ]; then
    rm cscope.*
fi
find ./ -name '*.h' -o -name '*.c' -o -name '*.cpp' -o -name 'Makefile*'> cscope.files
cscope -b -k -q
ctags -R
