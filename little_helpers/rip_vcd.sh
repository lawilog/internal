#!/bin/bash
DEV_CDROM="/dev/cdrom"

dir="`iso-info ${DEV_CDROM} | grep Volume | while read a b c d; do echo $c; break; done`"
echo "creating dir $dir"
mkdir -p "$dir"
cd "$dir"

echo "ripping..."
vcdxrip -v -C /dev/cdrom

rm videocd.xml

i=1
while true
do
	name="${dir}_cd${i}.mpg"
	test -e "$name" || break
	i=$[$i+1]
done
mv avseq01.mpg "$name"

eject $DEV_CDROM
