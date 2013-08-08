#!/bin/bash
# This will automatically suspend /dev/sd* disks, when there
# was no I/O activity for (CHECK_INTERVAL * COUNT) seconds.
# Make sure that iostat and hdparm are installed.
CHECK_INTERVAL=600
COUNT=6

declare -A counts
iostat -d $CHECK_INTERVAL $(ls /dev/sd?) | while read dev tps R
do
	test "${dev:0:2}" = "sd" || continue
	if [ "$tps" = "0,00" ]
	then
		# echo "$dev was idle"
		test -z "${counts[$dev]}" && counts[$dev]=0
		if [ ${counts[$dev]} -eq $COUNT ]
		then
			logger Suspending idle $dev
			hdparm -y /dev/$dev
		fi
		counts[$dev]=$(( ${counts[$dev]} + 1 ))
	else
		# echo "$dev was busy"
		counts[$dev]=0
	fi
done
