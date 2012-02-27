#!/bin/bash

echo - loading device mapper
modprobe dm-mod

echo
echo - starting betaftpd
betaftpd start

echo
echo - chancing user password for user knoppix
passwd knoppix

echo
echo - starting sshd
sshstart

if [ "$1" == "" ]
then
	echo "use: $0 device (sda, sdb1, ...)"
	exit 1
fi
if [ ! -b /dev/$1 ]
then
	echo "device /dev/$1 seems not to exist"
fi
if [ -b /dev/mapper/$1 ]
then
	./cryptsetup_luks remove $1
fi

echo
echo "- setting encryption mapper"
./cryptsetup_luks -c aes-cbc-essiv:sha256 -h ripemd160 create $1 /dev/$1

echo
if [ -x /mnt/$1 ]
then
	echo "mount point /dev/$1 exists"
else
	echo "- creating mountpoint /mnt/$1"
	mkdir /mnt/$1
fi

echo
echo "- mounting /dev/mapper/$1 into /mnt/$1"
if mount -o ro /dev/mapper/$1 /mnt/$1
then
	echo "- listing /mnt/$1"
	ls -l /mnt/$1
else
	./cryptsetup_luks remove $1
fi

