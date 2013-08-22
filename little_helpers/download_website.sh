#!/bin/bash
url="$1"
domain=$( echo "$url" | sed 's|^http://||;s|/.*||' )
wget -r -k -p -nc -np -E --restrict-file-names=ascii -D $domain "$url"
