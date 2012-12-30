#!/bin/bash
dir=~/video/eRep/
wget "http://www.zdf.de/ZDFmediathek/kanaluebersicht/aktuellste/640618?teaserListIndex=52&bc=rub;kua884730;kua640618&flash=off" -O - 2>/dev/null | grep '/ZDFmediathek/beitrag' | sed 's/.*href="//g;s/".*//g' | sort | uniq | while read url
do
	asxurl=$( wget "http://www.zdf.de/$url" -O - 2>/dev/null | grep asx | sort | tail -1 | sed 's/.*href="//g;s/".*//g' )
	download_video.sh "$asxurl" "$dir"
done
