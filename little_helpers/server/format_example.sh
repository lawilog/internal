exit 1

mount -o remount,rw /mnt/keymaker
dd if=/dev/random of=/mnt/keymaker/seraph.key bs=1 count=256
mount -o remount,ro /mnt/keymaker
cryptsetup luksFormat /dev/sdb3 /mnt/keymaker/seraph.key -c aes-cbc-essiv:sha256
cryptsetup luksAddKey /dev/sdb3 -d /mnt/keymaker/seraph.key -y
cryptsetup luksOpen /dev/sdb3 seraph -d /mnt/keymaker/seraph.key
mkfs.ext4 -m 0 -L seraph /dev/mapper/seraph
cryptsetup luksDump /dev/sdb3 | grep UUID
nano cmount
cmount /dev/sdb3
chown architect:users /mnt/seraph/
