#!/bin/bash
imdbID="$1"
which curl &> /dev/null || echo "Error. Please install curl"
url="www.imdb.com/title/$imdbID/"
titleyear="$(curl -s "$url" | tr '\n' ' ' | grep -o '<title>.*</title>' | head -1 | sed -r 's|</*title>||g; s| - IMDb$||; s| *\(([0-9]*)\)$|\t\1|g')"
echo -e "$url\t$titleyear"
