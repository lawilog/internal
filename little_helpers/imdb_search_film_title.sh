#!/bin/bash
title="$1"
which curl &> /dev/null || echo "Error. Please install curl"
which tidy &> /dev/null || echo "Error. Please install tidy"
curl -G -s --data "s=tt" --data "ttype=ft" --data-urlencode "q=$title" http://www.imdb.com/find | \
	tidy -utf8 -q -w 1000 2>/dev/null | \
	sed 's|<a|\n<a|g; s|</td>|</td>\n|g; s|&amp;|and|g' | \
	grep '<a href="/title/tt' | grep -v '<img' | \
	sed -nr 's#<a href="/title/(tt[0-9]*)/.*">(.*)</a> *(.*)</td>#www.imdb.com/title/\1/\t\2\t\3#pg' | \
	sed -r 's#\t\(([0-9]{4})\)$#\t\1\t#g; s#\t\((.*)\) \(([0-9]{4})\)$#\t\2\t\1#g; s#\t\((.*)\)$#\t\t\1#g'

