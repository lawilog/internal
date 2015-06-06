#!/bin/bash
# accept both command line argument and pipe
if [ $# -eq 0 ]; then while read f; do $0 "$f"; done; exit $?; fi

# take file. if dir is given, find largest file in dir
f=$(find "$@" -exec stat -L --printf="%s " {} \; -print | sort -n -r | head -1 | while read a b; do echo "$b"; done)

mediainfo "$f" | awk '
	/Width/{ gsub(/(.*: | |pixels)/, "", $0); W=1*$0}
	/Height/{gsub(/(.*: | |pixels)/, "", $0); H=1*$0}
	END{
		R="";
		if(W && H) {
			if(W<640) R="low quali";
			if(W>=640 || H>=480) R="480p";
			if(H>=576) R="576p";
			if(W>=1280 || H>=720) R="720p";
			if(W>=1920 || H>=1080) R="1080p"
		};
		print R
	}'
