#!/bin/bash
# accept both command line argument and pipe
if [ $# -eq 0 ]; then while read f; do $0 "$f"; done; exit $?; fi

# take file. if dir is given, find largest file in dir
f=$(find "$@" -exec stat -L --printf="%s " {} \; -print | sort -n -r | head -1 | while read a b; do echo "$b"; done)

echo $(mediainfo '--Output=Audio;%Language%,' "$f")$(mediainfo '--Output=Text;%Language%,' "$f" | sed 's/,/-sub,/g; s/,$//')
