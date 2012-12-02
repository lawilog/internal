#!/bin/bash
url="$1"
echo "$url" | grep '.asx$' &> /dev/null && url=$( wget $url -O - 2> /dev/null | grep "href=" | sed 's/.*href="//g;s/".*//g' )
savename=~/video/$( basename "$url" )
echo mplayer "$url" -dumpstream -dumpfile "${savename}"
mplayer "$url" -dumpstream -dumpfile "${savename}"
