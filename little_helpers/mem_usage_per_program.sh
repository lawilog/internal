#!/bin/bash
declare -A pa
while read B p c
do
	p=$(basename $p)
	test $? -eq 1 && continue
	pa["$p"]=$(( ${pa["$p"]} +$B ))
done < <(ps -e -orss=,args= | egrep -v ' *0 *\[') &> /dev/null
n=0
S=0
(for p in "${!pa[@]}"
do
	echo ${pa["$p"]} $p
done | sort -n -r; echo) | while read B p
do
	if [ -z "$p" ]
	then
		#echo -e "\n$(printf '%8i' $S) Other Programs"
		printf '\n%10s' "$( echo $((1024*$S)) | B2h.sh )"
		echo "  Other Programs"
		break
	fi
	if [ $n -lt 20 ]
	then
		#echo "$(printf '%8i' $B) $p"
		printf '%10s' "$( echo $((1024*$B)) | B2h.sh )"
		echo "  $p"
	else
		S=$(( $S + $B ))
	fi
	n=$(( $n + 1 ))
done
