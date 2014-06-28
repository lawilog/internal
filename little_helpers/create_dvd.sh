#!/bin/bash
inf="$1"
outp="$2"
test -z "$outp" && echo "usage: $0 input_file.avi output_prefix" && exit 1

ffmpeg -i "$inf" -y -target ntsc-dvd -sameq -aspect 16:9 "$outp".mpg
dvdauthor --title -o "$outp" -f "$outp".mpg
VIDEO_FORMAT=NTSC dvdauthor -o "$outp" -T
mkisofs -dvd-video -o "$outp".iso "$outp"/
