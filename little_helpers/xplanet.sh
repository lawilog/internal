#!/bin/bash
n="$[`date +%k`*60+`date +%M`]"
if [ $n -gt $[12*60] ]
then	# pm
	n=$[$[36*60]-$n]
else	# am
	n=$[$[12*60]-$n]
fi
n=`echo $n*360/1440.0 | bc`
#echo n=$n
xplanet -config ~/.xplanet/default -radius 42 -latitude 35 -longitude $n --geometry $1 --num_times 1 --output $2.jpg && mv $2.jpg $2
