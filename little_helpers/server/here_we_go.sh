#!/bin/bash
keymaker.sh || exit 1
ramlinks.sh recreate
mount --bind /mnt/morpheus/drop/ /mnt/drop
service nfs-kernel-server status && service nfs-kernel-server reload || service nfs-kernel-server start

mount --bind /mnt/trainman/mysql /var/lib/mysql
chown mysql -R /var/lib/mysql
service mysql restart
