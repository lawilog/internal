#!/bin/bash
WH=( $(wmctrl -d | grep '*' | awk '{print $4}' | awk -Fx '/x/{w+=$1; h+=$2} END{print w-8, h-96}') )
W=${WH[0]}
H=${WH[1]}
# echo "W = $W , H = $H"
wmctrl -r :ACTIVE: -b remove,maximized_vert,maximized_horz
wmctrl -r :ACTIVE: -e "0,4,29,$W,$H"
