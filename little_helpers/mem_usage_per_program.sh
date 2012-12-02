#!/bin/bash
declare -A pa
while read B p c
do
	p=$(basename $p)
	pa["$p"]=$(( ${pa["$p"]} +$B ))
done < <(ps -e -orss=,args= | egrep -v ' *0 *\[')
for p in "${!pa[@]}"
do
	echo ${pa["$p"]} $p
done | sort -n -r | while read B p
do
	echo "$(printf '%8i' $B) $p"
done | head -30
