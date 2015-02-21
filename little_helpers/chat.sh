#!/bin/bash
chatfile=/mnt/manifest/chat
touch "$chatfile"
chmod 666 "$chatfile"
echo "# type messages below and press enter. run another terminal with: tail -f $chatfile"
while read L
do
	# echo [$(date +"%Y-%m-%d %H:%M:%S")] $(whoami): "$L" >> "$chatfile"
	(echo -en "\033[00;$((32+$UID%1000))m["$(date +"%Y-%m-%d %H:%M:%S")"]\033[01;$((32+$UID%1000))m $(whoami):\033[00m "; echo "$L") >> "$chatfile"
done
