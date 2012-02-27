#!/bin/bash
progs="pidgin skype thunderbird yarssr"
softlevel=`rc-status --runlevel`
case "$softlevel" in
default)
	for p in $progs
	do
		ps | grep -q $p || $p &> /dev/null &
	done
	;;
nonetwork)
	for p in $progs
	do
		killall $p
	done
	;;
esac
