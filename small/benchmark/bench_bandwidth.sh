#!/bin/bash
gcc -O3 limit_bandwidth.c -o limit_bandwidth

for N in 100 1000 10000 40000
do
	for f in 0.0 0.25 0.5 0.75 1.0
	do
		echo "N = $N , f = $f"
		time ./limit_bandwidth $N $f
	done
done 2>&1 | tee c_bandwidth.log

