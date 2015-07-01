#!/bin/bash
# cat /mnt/drop/movielist_20150628_commarec.txt |
while read dir
do
	imdbUrl=$(head -1 "$dir/movie.nfo")
	imdbUrlHash=$(echo -n "$imdbUrl" | md5sum | awk '{print $1}')
	f=$(find "$dir" -exec stat -L --printf="%s " {} \; -print | sort -n -r | head -1 | while read a b; do echo "$b"; done)
	echo -en "${dir}\t${imdbUrl}\t${imdbUrlHash}\t"
	~/proggen/projects/m3dsync/m3dsync hash "$f"
done # > /mnt/drop/movielist_20150628_commarec_urls.txt
