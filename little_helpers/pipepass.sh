#!/bin/bash
# usage: output_cmd | ./pipecall.sh process_cmd [options]
# e.g. echo -e "foo bar\nyolo" | ./pipepass.sh echo

while read x; do L[${#L[*]}]="$x"; done
"${@}" "${L[@]}"
