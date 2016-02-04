#!/bin/bash
gcc -O3 limit_flops.c -o limit_flops
(time ./limit_flops 500) 2>&1 | tee c_flops.log
