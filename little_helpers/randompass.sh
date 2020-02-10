#!/bin/bash
w=${1:-14}
n=${2:-8}
# c=${3:-'[[:alnum:]]!#$%&()*+,-./:;<=>?@[\]^_{|}'} # '[:alnum:]%+-./=_'
c=${3:-[:alnum:]}
cat /dev/urandom | tr -cd "$c" | fold -w "$w" | head -n "$n"
