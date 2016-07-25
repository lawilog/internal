#!/bin/bash
# nonsense. use uniq -c instead.
n=-1
last=""
while read L
do
	if [[ $n -eq -1 || "$L" == "$last" ]]
	then
		n=$(($n + 1))
	else
		printf "%5i %s\n" $n "$last"
		n=0
	fi
	last="$L"
done
