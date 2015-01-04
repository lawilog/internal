#!/bin/bash
w=${1:-8}
n=${2:-10}
c=${3:-'[[:alnum:]]!#$%&()*+,-./:;<=>?@[\]^_{|}'}
cat /dev/urandom | tr -cd "$c" | fold -w "$w" | head -n "$n"
