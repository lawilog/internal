#!/bin/bash
inf="$1"
outf="${2:-${inf}_1080p.mkv}"
tmpf="${outf}_tmp.mkv"
echo "$inf -> $outf"

# use x264 to convert video
x264 --vf resize:1920,1080 -o "$tmpf" "$inf"

# merge video and audio into one file
ffmpeg -i "$tmpf" -i "$inf" -c:v copy -c:a mp3 -map 0:v0 -map 1:a:0 "$outf"
rm "$tmpf"
