#!/bin/bash
w=${1:-12}
n=${2:-8}
c=${3:-'ABCDEFGHJLMNPQRSTWXY23456789abdefghijpqrstwxyz=+-'}
# '[[:alnum:]]!#$%&()*+,-./:;<=>?@[\]^_{|}'
# '[:alnum:]%+-./=_'
cat /dev/urandom | tr -cd "$c" | fold -w "$w" | head -n "$n"
