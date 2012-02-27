#!/bin/bash
mntimg="/mnt/image.lnk"
mntpt="/mnt/image"
echo current: `ls -l "${mntimg}"`
test -z $1 && read -p "Enter iso path: " iso || iso=$1
umount "${mntpt}"
ln -sf "${iso}" "${mntimg}" || read enter
mount "${mntpt}" || read enter
#/usr/kde/3.5/bin/konqueror ${mntimg} &
