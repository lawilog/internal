#!/bin/bash
if [ $# -eq 0 ]; then while read dir; do $0 "$dir"; done; exit $?; fi

for dir # in "$@"
do
	if [ ! -d "$dir" ]
	then
		echo "ERROR: Could not open \"$dir\"."
		continue
	fi

	movienfo="$dir/movie.nfo"
	imdbCandidatesFile="$dir/imdb_candidates.dat"
	imdbTempListFile="${imdbCandidatesFile}.temp"

	# maybe we already have an movie.nfo?
	if [ -e "$movienfo" ]
	then
		imdbLinks=$( egrep -o 'www.imdb.com/title/tt[0-9]*' "$movienfo" | tr '\n' ' ' )
		if [ -n "$imdbLinks" ]
		then
			echo "# Skipping dir \"$dir\", because I found imdb links in movie.nfo: $imdbLinks"

			test -e "$imdbCandidatesFile" && echo "# Cleaning dat" && rm -v "$imdbCandidatesFile"

			continue
		else
			imdbID=$(sed -nr 's| *<imdb>(.*)</imdb>|\1|p' "$movienfo" | head -1)
			if [ -n "$imdbID" ]
			then
				echo "# Rewriting movie.nfo in \"$dir\", because I found <imdb> tag: $imdbID"
				imdb_query_title_year_by_id.sh "$imdbID" | tr '\t' '\n' > "$movienfo"

				test -e "$imdbCandidatesFile" && echo "# Cleaning dat" && rm -v "$imdbCandidatesFile"

				continue
			fi
		fi
	fi

	# check if candidates are listed in file. if not, create that file
	if [ ! -e "$imdbCandidatesFile" ]
	then
		dirtitle=$(media_explode_dirname.sh "$(basename "$dir")" | awk -F'\t' '{print $1}')
		diryear=$( media_explode_dirname.sh "$(basename "$dir")" | awk -F'\t' '{print $2}' | sed 's/\[\|\]//g')

		# frist, online query for candidates
		combi_explode.sh - "$dirtitle" | while read qtitle
		do
			imdb_search_film_title.sh "$qtitle"
		done > "$imdbTempListFile"

		# second, scan existing nfo files for more candidates
		(cd "$dir"; egrep -Ho 'www.imdb.com/title/tt[0-9]*' *.nfo 2>/dev/null | sed 's/:/ : /')
		egrep -ho 'www.imdb.com/title/tt[0-9]*' "$dir"/*.nfo 2>/dev/null | while read imdbUrl
		do
			imdbID=$(echo "$imdbUrl" | egrep -o 'tt[0-9]+')
			imdb_query_title_year_by_id.sh "$imdbID"
		done >> "$imdbTempListFile"

		# now, asign matching points (MP) to the candidates
		cat "$imdbTempListFile" | sort | uniq | while read imdbcandidate
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
		done | sort -n -k1 -r | uniq > "$imdbCandidatesFile"

		rm "$imdbTempListFile"
	fi

	N=$(cat "$imdbCandidatesFile" | wc -l)
	awk '(NF>0) {print "[" ++n "]\t" $0}' "$imdbCandidatesFile" | tac
	guessedtitle="$(mediainfo_title.sh "$dir")"
	echo -e "dir, title: \033[01;36m\"${dir}\"\033[00m, \033[01;32m\"${guessedtitle}\"\033[00m"
	case "$N" in
		0) echo "No idea. Enter  s to skip  or  a string containg tt for an imdb id." ;;
		1) echo "Enter 1 to accept candidate or  s to skip  or  a string containg tt for own imdb id." ;;
		*) echo "$N candidates. Enter any of the above numbers or  s to skip  or  a string containg tt for own imdb id." ;;
	esac
	while true
	do
		read -p "? " choice < /dev/tty
		if [ "$choice" = "s" -o "$choice" = "S" ]
		then
			echo "# Skipped."
		elif (echo "$choice" | egrep -q 'tt[0-9]+')
		then
			imdbID=$(echo "$choice" | egrep -o 'tt[0-9]+')
			imdb_query_title_year_by_id.sh "$imdbID" | tr '\t' '\n' | tee "$movienfo"
			rm "$imdbCandidatesFile"
			echo "# Done."
		elif [ 1 -le $(echo "$choice" | awk '{print 1*$1}') -a $(echo "$choice" | awk '{print 1*$1}') -le $N ]
		then
			sed -n "$choice"p "$imdbCandidatesFile" | tr '\t' '\n' | tail -n +2 | tee "$movienfo"
			rm "$imdbCandidatesFile"
			echo "# Done."
		else
			echo "What?"
			continue
		fi
		break
	done
	# sleep 1
	echo
done
