#!/bin/bash
w=${1:-8}
n=${2:-10}
cat /dev/urandom | tr -cd '[[:alnum:]]!#$%&()*+,-./:;<=>?@[\]^_{|}' | fold -w $w | head -n $n
