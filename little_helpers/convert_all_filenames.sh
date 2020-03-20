#!/bin/bash
pat="^[[:alnum:] _-\.,\'{}\(\)/&~]*$"
# | egrep -v "$pat"
find $@ | while read p; do
	d=$(dirname  "$p")
	f=$(basename "$p")
	# if already good, dont try correction
	if echo "$f" | egrep -q "$pat"; then continue; fi

	for c in ISO_8859-15 CP437 IBM850; do # see iconv -l for a complete list
		fc=$(echo "$f" | iconv -f "$c" -t UTF-8)
		if [ "$fc" = "$f" ]; then continue; fi
		# only if new name is good, do rename
		if echo "$fc" | egrep -q "$pat"; then mv -vi "$p" "$d/$fc"; break; fi
	done
	test -e "$p" && echo "# $p"
done | uniq
