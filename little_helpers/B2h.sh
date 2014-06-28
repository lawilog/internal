#!/bin/bash
x=$1
pre=("" Ki Mi Gi Ti Pi Ei Zi)
if [ -z "$x" ]; then
	while read x R; do
		n=$( echo "$x" | awk '{print int(log($1)/log(1024))}' )
		echo $(echo $x $n ${pre[$n]}B | awk '{if($2==0) printf("%i %s\n", $1, $3); else printf("%.1f %s\n", $1/(1024^$2), $3);}') "$R"
	done
else
	shift
	R=$@
	n=$( echo "$x" | awk '{print int(log($1)/log(1024))}' )
	echo $(echo $x $n ${pre[$n]}B | awk '{if($2==0) printf("%i %s\n", $1, $3); else printf("%.1f %s\n", $1/(1024^$2), $3);}') "$R"
fi
