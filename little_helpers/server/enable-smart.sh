#!/bin/bash
devs="$@"
test -z "$devs" && devs=$(ls /dev/sd?)
for dev in $devs
do
	smartctl --smart=on --offlineauto=on --saveauto=on $dev
	smartctl -t offline $dev
	hdparm -S 120 $dev
done
