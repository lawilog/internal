#!/bin/bash
pos=$1            # left right top bottom full
screen=${2:-0}    # default 0, else 1, 2, ...

subW=10
subH=24
deskDim=$( wmctrl -d | grep '*' | awk '{print $9}' )

case $deskDim in
	3840x1055)
		deskW=(1920 1920)
		deskH=(1055 1080)
	;;

	2880x995)
		deskW=(1280 1600)
		deskH=( 995  900)
	;;

	3520x1051)
		deskW=(1920 1600)
		deskH=(1051  900)
		;;

	*)
		deskW=$( echo $deskDim | sed 's/x/ /' | awk '{print $1}' )
		deskH=$( echo $deskDim | sed 's/x/ /' | awk '{print $2}' )
	;;
esac

# xrandr | grep connected | sed -r 's/ ([0-9]+)x([0-9]+)/\nTOKEN \1 \2 /g; s/\+/ /g' | grep TOKEN | sort -n -k4 | awk '{print $2, $3}'

offsetX=0
offsetY=0
for(( s=0; s<screen; ++s ))
do
	offsetX=$(( $offsetX + ${deskW[$s]} ))
	# offsetY=$(( $offsetY + ${deskH[$s]} ))
done
deskW=(${deskW[$screen]})
deskH=(${deskH[$screen]})

# echo "deskW = $deskW , deskH = $deskH"

winW=$deskW
winH=$deskH
case $pos in
	left)
		winW=$(( $deskW / 2 ))
	;;
	
	right)
		offsetX=$(( $offsetX + $deskW / 2 ))
		winW=$(( $deskW / 2 ))
	;;
	
	top)
		winH=$(( $deskH / 2 ))
	;;
	
	bottom)
		offsetY=$(( $offsetY + $deskH / 2 ))
		winH=$(( $deskH / 2 ))
	;;
esac
winW=$(( $winW - $subW ))
winH=$(( $winH - $subH ))

wmctrl -r :ACTIVE: -b remove,maximized_vert,maximized_horz
wmctrl -r :ACTIVE: -e "0,$offsetX,$offsetY,$winW,$winH"

