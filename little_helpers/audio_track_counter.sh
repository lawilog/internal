#!/bin/bash
num=`echo "q" | mplayer -vo null "$1" 2> /dev/null | grep Audiostream | wc -l`
if [ $num -gt 1 ]
then
	echo $1
fi
