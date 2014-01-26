#!/bin/bash
keymaker.sh
ramlinks.sh recreate
mount --bind /mnt/morpheus/drop/ /mnt/drop
service nfs-kernel-server status && service nfs-kernel-server reload || service nfs-kernel-server start

