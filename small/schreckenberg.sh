#!/bin/bash
n=500
i=1
f="dens.dat"
#rm $f
touch $f
while [ $i != $n ]
do
	# echo $i
	echo -n -e "$i\t" >> $f
	./schreckenberg $n $i 1000 5 0.75 >> $f
	i=$[$i+1]
done
