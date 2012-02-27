#!/bin/bash
if [ "$1" = "go" ]
then
	xsetroot -solid darkblue
	VBoxManage startvm WinXP
	while true
	do
		sleep 20
		VBoxManage showvminfo WinXP | grep State | grep running || exit
	done
else
	xinit $0 go -- :2
fi
