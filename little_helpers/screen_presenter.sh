#!/bin/bash
mode=$1 # on off menu
tmpf=$(tempfile)
xrandr --query > "$tmpf"
A=( $(awk '/ connected/{print $1}' "$tmpf") )
# echo "A =  ${A[@]}" # LVDS1 VGA1
myMaxRes=$(awk "(x){print \$1; x=0}; /^${A[0]}/{x=1}" "$tmpf")
echo "# mymaxRes = $myMaxRes"
case "$mode" in
	on)
		if [ ${#A[@]} -gt 1 ]; then
			presenterMaxRes=$(awk "(x){print \$1; x=0}; /^${A[1]}/{x=1}" "$tmpf")
			echo "# presenterMaxRes = $presenterMaxRes"
			scale=$(echo "${presenterMaxRes}x${myMaxRes}" | awk -Fx '{print $1/$3 "x" $2/$4}')
			xrandr --output ${A[0]} --auto --scale $scale --output ${A[1]} --auto --same-as ${A[0]}
		else
			echo "Error: no second screen found. Is Cable connected?"
		fi
		;;

	off)
		cmd="xrandr --output ${A[0]} --auto --mode $myMaxRes --scale 1x1"
		for ((i=1; i<${#A[@]}; ++i)); do
			cmd="$cmd --output ${A[$i]} --off"
		done
		$cmd
		;;

	*)
		arandr &> /dev/null
		;;
esac
rm "$tmpf"
