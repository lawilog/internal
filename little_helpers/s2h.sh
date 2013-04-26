#!/bin/bash
test -z "$1" && s=$(read x && echo "$x" ) || s="$1"
echo -n "$s = "
test $s -lt 60 && echo "${s}s" && exit
min=$(( $s / 60 ))
s=$(( $s % 60 ))
test $min -lt 60 && echo "${min}min ${s}s" && exit
h=$(( $min / 60 ))
min=$(( $min % 60 ))
test $h -lt 24 && echo "${h}h ${min}min ${s}s" && exit
d=$(( $h / 24 ))
h=$(( $h % 24 ))
test $d -lt 365 && echo "${d}d ${h}h ${min}min ${s}s" && exit
a=$(( $d / 365 ))
d=$(( $d % 365 ))
echo "${a}a ${d}d ${h}h ${min}min ${s}s"
