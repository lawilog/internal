#!/bin/bash
losetup /dev/loop5 /root/keymaker && \
cryptsetup luksOpen /dev/loop5 keymaker && \
mount -o ro /dev/mapper/keymaker /mnt/keymaker && \
for d in /dev/sd*; do /root/bin/cmount $d; done && \
umount /mnt/keymaker && \
cryptsetup luksClose keymaker && \
losetup -d /dev/loop5
