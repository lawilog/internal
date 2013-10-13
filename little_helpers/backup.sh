#!/bin/bash

rsync deusex:: | grep lawilog-backup && \
	rsync --delete-during -aE --log-file=/tmp/rsync.log /home/lawilog/ deusex::lawilog-backup && \
	echo "[`date`] Backup done." || \
	echo "[`date`] Could not backup."

# mount | grep neo && \
#	rsync --delete-during -aE --log-file=/tmp/rsync.log /home/lawilog/ /mnt/neo/backup/lawilog > /dev/null && \
#	echo "[`date`] Backup done." || \
#	echo "[`date`] Could not backup."
