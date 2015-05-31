#!/bin/bash
f="$1"
name=$(mediainfo "$f" | awk '/^Movie name/{gsub(/.*: /, "", $0); print $0}' )
if [ "$name" == "" ]; then name=$(mediainfo "$f" | awk '!/:/{x=($1=="Video")}; /Title/{if(x) {gsub(/.*: /, "", $0); print $0}}' ); fi
if [ "$name" == "" ]; then name=$(basename "$f" | sed 's/[\._-]/ /g; s/ *$//'); fi
name=$( echo "$name" | sed 's/\(1080\|720\|x264\|xvid\|dvd\|blueray\|hdtv\|german\|unrated\|encode\| by \|\.mkv\|\.avi\|\.mpg\|\.mpeg\).*$//gI; s/\((\)\([0-9]\{4\}\)\()\)/[\2]/g;s/(\|)//g' )
echo "$name"
