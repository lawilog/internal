#!/bin/bash
# This will automatically suspend /dev/sd* disks, when there
# was no I/O activity for (CHECK_INTERVAL * COUNT) seconds.
# Make sure that iostat and hdparm are installed.
CHECK_INTERVAL=15
COUNT=4
devs=( $(ls /dev/sd?) )
declare -A counts
iostat -d 15 ${devs[@]} | while read dev tps R
do
	test "${dev:0:2}" = "sd" || continue
	if [ "$tps" = "0,00" ]
	then
		counts[$dev]=$(( ${counts[$dev]} + 1 ))
		# echo "$dev was idle, ${counts[$dev]}"
		test ${counts[$dev]} -eq $COUNT && hdparm -y /dev/$dev
	else
		counts[$dev]=0
		# echo "$dev was busy, ${counts[$dev]}"
	fi
done
