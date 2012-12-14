#!/bin/bash
title="  G  M  K"
echo "$title"
declare -A pa
while read B p c
do
	p=$(basename $p)
	pa["$p"]=$(( ${pa["$p"]} +$B ))
done < <(ps -e -orss=,args= | egrep -v ' *0 *\[')
n=0
S=0
(for p in "${!pa[@]}"
do
	echo ${pa["$p"]} $p
done | sort -n -r; echo) | while read B p
do
	if [ -z "$p" ]
	then
		echo -e "\n$(printf '%8i' $S) Other Programs\n$title"
		break
	fi
	if [ $n -lt 20 ]
	then
		echo "$(printf '%8i' $B) $p"
	else
		S=$(( $S + $B ))
	fi
	n=$(( $n + 1 ))
done
