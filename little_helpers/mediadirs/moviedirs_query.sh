#!/bin/bash
#head /mnt/drop/movielist_20150606_commarec.txt | 
while read dir
do
	f="$dir/imdb_match_candidates.dat"
	echo -n > "$f"
	title=$(media_explode_dirname.sh "$(basename "$dir")" | awk -F'\t' '{print $1}')
	combi_explode.sh - "$title" | while read qtitle
	do
		echo "$qtitle"
		imdb_search_film_title.sh "$qtitle" >> "$f"
	done
done
