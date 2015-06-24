#!/bin/bash
for dir in "$@"
do
	find -L "$dir" -mindepth 1 -maxdepth 1 -type d | while read subdir
	do
		media_explode_dirname.sh "$(basename "$subdir")" | awk -F'\t' '{print $1}' | grep -q , && $0 "$subdir" || echo "$subdir"
	done
done
