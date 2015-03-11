#!/bin/bash
s="$1"
shift
msg="${@}"
test -z "$s" && read s msg
printf "%9i = " "$s"
test $s -lt 60 && echo -e "${s}s $msg\t${msg}" && exit
min=$(( $s / 60 ))
s=$(( $s % 60 ))
test $min -lt 60 && echo -e "${min}min ${s}s\t${msg}" && exit
h=$(( $min / 60 ))
min=$(( $min % 60 ))
test $h -lt 24 && echo -e "${h}h ${min}min ${s}s\t${msg}" && exit
d=$(( $h / 24 ))
h=$(( $h % 24 ))
test $d -lt 365 && echo -e "${d}d ${h}h ${min}min ${s}s\t${msg}" && exit
a=$(( $d / 365 ))
d=$(( $d % 365 ))
echo "${a}a ${d}d ${h}h ${min}min ${s}s"
