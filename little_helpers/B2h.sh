#!/bin/bash
x=$1
if [ -z "$x" ]; then while read y; do x=$y; done; fi
x=$(( $x ))
n=0
while [ $x -gt 1024 ]
do
	x=$(( $x / 1024 ))
	n=$(( $n + 1))
done
pre=("" Ki Mi Gi Ti Pi Ei Zi)
echo "${x} ${pre[$n]}B"
