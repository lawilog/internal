#!/bin/bash
logfile="/tmp/rsync.log"
host="manifest"
target="lawilog-backup"
dir="/home/lawilog/"

echo "`date +"%Y/%m/%d %H:%M:%S"` Starting backup from $dir to $host::$target" >> "$logfile"

/bin/ping -c 1 -w 1 $host &> /dev/null || \
{
	echo "`date +"%Y/%m/%d %H:%M:%S"` Host $host is not up :-(" >> "$logfile" ;
	exit ;
}

rsync $host:: | grep $target || \
{
	echo "`date +"%Y/%m/%d %H:%M:%S"` Host $host does not provide rsync target $target :-(" >> "$logfile" ;
	exit ;
}

rsync --delete-during -aE --log-file="$logfile" "$dir" $host::$target &> /dev/null || \
{
	echo "`date +"%Y/%m/%d %H:%M:%S"` Rsync backup failed :-(" >> "$logfile" ;
	# put your extra alarming suff here ^^
        exit ;
} \
&& \
{
	echo "`date +"%Y/%m/%d %H:%M:%S"` Backup from $dir to $host::$target completeted successfull :-)" >> "$logfile" ;
}
