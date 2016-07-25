#!/bin/bash
gcc -std=c99 -O3 -Wpedantic benchmark.c -o benchmark -lpthread

log="${1:-benchmark.log}"
M=${2:-1280}
(echo -e "10 1 0 0\n 10 1 0 0.05\n 10 16 0 0\n 2 1 10 0\n 2 16 10 0" | while read N t c d
do
	time (for i in $(seq 1 $N); do echo "== ./benchmark $t $M $c $d =="; time ./benchmark $t $M $c $d; done; echo "$N times needed:")
done
) 2>&1 | tee "$log"
