#!/bin/bash
pos=$1            # left right top bottom
screen=${2:-0}    # default 0, else 1, 2, ...

subW=10
subH=24
deskDim=$( wmctrl -d | grep '*' | awk '{print $9}' )

case $deskDim in
	2880x995)
		deskW=(1280 1600)
		deskH=( 995  900)	
	;;
	
	*)
		deskW=$( echo $desktop_dim | sed 's/x/ /' | awk '{print $1}' )
		deskH=$( echo $desktop_dim | sed 's/x/ /' | awk '{print $2}' )
	;;
esac

offsetX=0
offsetY=0
for(( s=0; s<screen; ++s ))
do
	offsetX=$(( $offsetX + ${deskW[$s]} ))
	# offsetY=$(( $offsetY + ${deskH[$s]} ))
done
deskW=(${deskW[$screen]})
deskH=(${deskH[$screen]})

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
winW=$(( $winW - subW ))
winH=$(( $winH - subH ))

wmctrl -r :ACTIVE: -b remove,maximized_vert,maximized_horz
wmctrl -r :ACTIVE: -e "0,$offsetX,$offsetY,$winW,$winH"
