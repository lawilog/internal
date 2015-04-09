#!/bin/bash
f=$(find "$@" -exec stat -L --printf="%s " {} \; -print | sort -n -r | head -1 | while read a b; do echo "$b"; done)
title=$(mediainfo_title.sh "$f")
comment=$(mediainfo_format.sh "$f")
lang=$(mediainfo_langs.sh "$f" | sed 's/ /,/g')
if [ "$comment" != "" ]; then comment=" -- $comment"; fi
if [ "$lang" != "" ]; then lang=" ($lang)"; fi
echo "${title}${comment}${lang}"
