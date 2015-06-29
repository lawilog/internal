#!/bin/bash
# accept both command line argument and pipe
if [ $# -eq 0 ]; then while read f; do $0 "$f"; done; exit $?; fi

# take file. if dir is given, find largest file in dir
f=$(find "$@" -exec stat -L --printf="%s " {} \; -print | sort -n -r | head -1 | while read a b; do echo "$b"; done)

movienfo="$(dirname "$f")/movie.nfo"
name=""
test -s "$movienfo" && name=$(sed -n 2p "$movienfo")
test "$name" == "" && name=$(mediainfo "$f" | awk '/^Movie name/{gsub(/.*: /, "", $0); print $0}' )
test "$name" == "" && name=$(mediainfo "$f" | awk '!/:/{x=($1=="Video")}; /Title/{if(x) {gsub(/.*: /, "", $0); print $0}}' )
test "$name" == "" && name=$(basename "$f" | sed 's/[\._-]/ /g; s/ *$//')
name=$( echo "$name" | sed 's/\(1080\|720\|x264\|xvid\|dvd\|blueray\|hdtv\|german\|unrated\|encode\| by \|\.mkv\|\.avi\|\.mpg\|\.mpeg\).*$//gI; s/\((\)\([0-9]\{4\}\)\()\)/[\2]/g;s/(\|)//g' )
echo "$name"
