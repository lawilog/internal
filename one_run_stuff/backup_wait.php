#!/usr/bin/php
<?php
while(true)
{
	if(file_get_contents('/root/backup_flag.txt')=='0') {echo "not copying\n"; sleep(20); continue;}
	$s=filesize('/mnt/alphabase/backup_medion/seagate.bin');
	sleep(30);
	clearstatcache();
	$s-=filesize('/mnt/alphabase/backup_medion/seagate.bin');
	if($s==0) system('play /usr/share/sounds/k3b_error1.wav');
	else echo "still copying\n";
	sleep(20);
}
?>
