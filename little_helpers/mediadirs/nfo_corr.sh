#!/bin/bash

find $1 -maxdepth 10 -mindepth 1 -name movie.nfo  | while read line; do
	test=$( cat "$line" | grep www.imdb.com/title )
	if [ -z "$test" ]
	then
		imdb_id=$( cat "$line" | grep '<imdb>' )
		imdb_id=${imdb_id#*>}
		imdb_id=${imdb_id%<*}
		echo "www.imdb.com/title/${imdb_id}" > "${line}"
		echo "WRITE to ${line}"
	elif [ ${#test} -ge 20 ]
	then
		echo "found correct imdb link ${test} in ${line}"
	else
		echo "ERROR in ${line}"
	fi
done
