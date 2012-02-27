#!/bin/bash
while true
do
	date +"%d.%m.%Y %H:%M:%S" >> ./still_alive.txt
	sleep 60
done
