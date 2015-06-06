#!/bin/bash
fa=$(tempfile)
fb=$(tempfile)

# echo "$1" | sed 's/\(.\)/\1\n/g' > "$fa"
# echo "$2" | sed 's/\(.\)/\1\n/g' > "$fb"
# echo $(diff -di "$fa" "$fb" | egrep '^<|^>' | wc -l) $(cat "$fa" | wc -l) $(cat "$fb" | wc -l) | awk '{printf("%i\n", 100*(1-$1/($2+$3)))}'

echo "$1" > "$fa"
echo "$2" > "$fb"
LC_ALL="C"  wdiff -si "$fa" "$fb" | awk '{e[x]=$5; x=!x;} END{printf("%i\n", e[0]<e[1]?e[0]:e[1])}' # (e[0]+e[1])/2

rm "$fa" "$fb"
