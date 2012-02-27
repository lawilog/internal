#!/bin/bash
echo "you may use $0 \"url\" \"filename\""
test -z "$1" && read -p "URL: " youtube_url || youtube_url="$1"
test -z "$2" && read -p "filename: " filename || filename="$2"
wget $(echo "http://youtube.com/get_video.php?$(curl -s $youtube_url | sed -n "/watch_fullscreen/s;.*\(video_id.\+\)&title.*;\1;p")") -O "$filename"
