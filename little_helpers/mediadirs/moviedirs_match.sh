#!/bin/bash
#head /mnt/drop/movielist_20150606_commarec.txt | 
while read dir
do
	echo -en "$dir\t"
	dirtitle=$(media_explode_dirname.sh "$(basename "$dir")" | awk -F'\t' '{print $1}')
	diryear=$( media_explode_dirname.sh "$(basename "$dir")" | awk -F'\t' '{print $2}' | sed 's/\[\|\]//g')
	f="$dir/imdb_match_candidates.dat"
	mlist="$dir/imdb_match_list.dat"
	(echo -e "\t\t\t"; test -s "$f" && cat "$f") | while read imdbcandidate
	do
		imdbtitle=$(  echo "$imdbcandidate" | awk -F'\t' '{print $2}')
		imdbyear=$(   echo "$imdbcandidate" | awk -F'\t' '{print $3}')
		imdbcomment=$(echo "$imdbcandidate" | awk -F'\t' '{print $4}')
		echo "$imdbcomment" | grep -q "in development" && continue
		MP=$(string_similarity.sh -bychar -avg "$imdbtitle" "$dirtitle")
		if [ -n "$diryear" -a  -n "$imdbyear" ]
		then
			d=$(( $diryear - $imdbyear ))
			test $d -lt 0 && d=$(( - $d ))
			MP=$(( $MP - 5 * $d ))
			test $MP -lt 0 && MP=0
		fi
		echo -e "${MP}\t${imdbcandidate}"
		found=1
	done | sort -n -k1 -r | uniq | tee "$mlist" | head -1
done
