#!/bin/bash
# usage: output_cmd | ./pipecall.sh process_cmd [options]
# e.g. echo -e "foo bar\nyolo" | ./pipecall.sh echo

while read x; do L[${#L[*]}]="$x"; done
for x in "${L[@]}"; do "${@}" "$x"; done
