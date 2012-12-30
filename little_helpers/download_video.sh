#!/bin/bash
url="$1"
dir="${2:-${HOME}/video}"
echo "$url" | grep '.asx$' &> /dev/null && url=$( wget $url -O - 2> /dev/null | grep "href=" | sed 's/.*href="//g;s/".*//g' )
savename=${dir}/$( basename "$url" )
if [ -e "${savename}" ]
then
	echo "File \"${savename}\" already exists. I will not overwrite it. If you want to re-download, delete that file first." 2>&1
else
	echo mplayer "$url" -dumpstream -dumpfile "${savename}"
	mplayer "$url" -dumpstream -dumpfile "${savename}"
fi
