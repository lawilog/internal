#!/bin/bash
for f in *
do
	mv "$f" "`echo $f | iconv -f ISO8859-15 -t UTF-8 - -o -`"
done
