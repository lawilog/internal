#!/bin/bash
killall sim && sim=1 || sim=0
killall kmail && kmail=1 || kmail=0

erg=`/usr/kde/3.5/bin/kdesu /usr/sbin/suspend2ram.sh` || xmessage "$erg"

if [ ! -z "`/etc/init.d/net.eth0 status | grep started`" ]
then
	test $kmail -eq 1 && /usr/kde/3.5/bin/kmail &
	test $sim -eq 1 && /usr/bin/sim &
	/home/lawilog/bibo.php &
fi
