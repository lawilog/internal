#!/bin/bash
url="$1"
type="$2"
tfile=$(tempfile)
wget "$url" -O "$tfile" -o /dev/null
baseurl=$( cat "$tfile" | tr '\n' ' ' | sed 's/\r//g;s/</\n</g' | egrep -i '^<base' | sed -n "/href/ s/.*href=['\"]\([^'\"]*\)['\"].*/\1/gp" || echo "$url" )
cat "$tfile" | grep_hrefs.sh | grep -i ".$type\$" | url_combine.sh "$url" | xargs -n 1 wget
rm "$tfile"
