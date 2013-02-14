#!/bin/bash
x=$1
test -z "$x" && x=$(read x && echo "$x")
pre=("" Ki Mi Gi Ti Pi Ei Zi)
n=$( echo "$x" | awk '{print int(log($1)/log(1024))}' )
echo $x $n ${pre[$n]}B | awk '{if($2==0) printf("%i %s\n", $1, $3); else printf("%.1f %s\n", $1/(1024^$2), $3);}'
