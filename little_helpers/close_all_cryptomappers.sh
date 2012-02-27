#!/bin/bash

fallback_cmd=exit 1

/etc/init.d/nfs stop || $fallback_cmd
/etc/init.d/samba stop || $fallback_cmd

cd /dev/mapper
for c in $(ls)
do
	if [ -b $c -a "$c" != "control" ]
	then
		echo Closing $c ...
		umount /dev/mapper/$c || $fallback_cmd
		cryptsetup luksClose $c || $fallback_cmd
	fi
done

/etc/init.d/nfs start || $fallback_cmd
/etc/init.d/samba start || $fallback_cmd
