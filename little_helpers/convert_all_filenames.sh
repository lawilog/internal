#!/bin/bash
pat="^[[:alnum:] _-.,\`'´{}()/&~]*$"
find $@ | egrep -v "$pat" | while read p; do
	d=$(dirname  "$p")
	f=$(basename "$p")
	for c in CP437 ISO_8859-15 IBM850; do # see iconv -l for a complete list
		fc=$(echo "$f" | iconv -f "$c" -t UTF-8)
		# only if new name is good, do rename
		echo "$fc" | egrep -q "$pat" && mv "$p" "$d/$fc" && break
	done
	test -e "$p" && echo "# $p"
done | uniq
