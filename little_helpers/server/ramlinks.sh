#!/bin/bash
ramdisk="/mnt/oracle"
dir=".drives"

not_mounted() {
mount | grep -q "$1 " && return 1 || return 0
}

case "$1" in
remove)
	echo "Removing all symlinks from $ramdisk"
	#exit 0
	find ${ramdisk} -mindepth 1 -path ${ramdisk}/${dir} -prune -o -exec find {} -type l -delete \;
	echo .
	find ${ramdisk} -mindepth 1 -path ${ramdisk}/${dir} -prune -o -exec find {} -mindepth 1 -type d -empty -delete \;
	;;

create)
	disk="$2"
	bindpath="${ramdisk}/${dir}/$disk"
	if [ -z "$disk" ]; then
		echo "supply DISK as command line argument"
		exit 1
	fi
	if not_mounted "/mnt/$disk"; then
		echo "/mnt/$disk not mounted"
		exit 1
	fi
	echo "Creating links for $disk"
	if not_mounted "$bindpath"
	then
		test -e "${ramdisk}/${dir}" || (mkdir -p "${ramdisk}/${dir}" && chown root:users "${ramdisk}/${dir}")
		mkdir -p "$bindpath"
		mount --bind /mnt/$disk "$bindpath"
	fi
	cp -rsp ${bindpath}/* ${ramdisk}/
	;;

recreate)
	$0 remove
	for disk in ghost merovingian morpheus niobe persephone trinity seraph smith # neo
	do
		$0 create $disk
	done
	;;

*)
	echo -e "usage:\n$0 remove - removes all symlinks from $ramdisk\n$0 create DISK - creates symlinks for DISK\n$0 recreate - removes and creates links for all disks"
	;;
esac
