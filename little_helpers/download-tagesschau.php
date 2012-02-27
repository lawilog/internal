#!/usr/bin/php
<?php
error_reporting(E_ALL);
$dir='/home/lawilog/tagesschau/';
$s='/multimedia/sendung/';
$l=intval(date('Ymd',strtotime('last month')));
function AlphaNum($str, $auch='')
{
	$erlaubt=html_entity_decode(':/.&?=-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789');
	$newstr=''; $len=strlen($str);
	for($i=0; $i<$len; $i++) if(strrpos($erlaubt,$str[$i])!==false) $newstr.=$str[$i];
	return $newstr;
}
for($i=0; $i<(date('d')<10?2:1); ++$i)
{	// search for latest files
	echo ($url='http://www.tagesschau.de/templates/pages/multimedia/date_select_broadcast.jsp?sophoraid=videoarchiv2&broadcastType=TS2000&select_month='.
	((date('n')-$i+11)%12+1).'&select_year='.($i==0?date('Y'):(date('Y')-(date('n')==1?1:0))).'&show=Anzeigen')."\n";
	$page=file_get_contents($url) or die("fatal: could not access http page\n");
	$pos=0; while(false !== $pos=strpos($page, $s, $pos+20))
	{	// open video page and look for download link
		echo ($url='http://www.tagesschau.de'.substr($page, $pos, strpos($page, '"', $pos+strlen($s))-$pos))."\n";
		$page2=file_get_contents($url) or die("fatal: could not access http page\n");
		if(false === $pos2=strpos($page2, 'H264')) echo "no download link found\n"; // catch exception: no download link
		else
		{
			$pos3=strrpos(substr($page2, 0, $pos2), 'http://');
			echo ($url=AlphaNum(substr($page2, $pos3, strpos($page2, '"', $pos3+7)-$pos3)))."\n";
			$d=substr(basename($url), 3, strpos(basename($url), '.')-3);
			if(intval($d)>$l && !is_file($target=$dir.$d{0}.$d{1}.$d{2}.$d{3}.'-'.$d{4}.$d{5}.'-'.$d{6}.$d{7}.'.h264.mp4'))
				system('echo '.$target.' && read x && test -z $x && wget -O '.$target.' "'.$url.'"');
		}
	}
}
// clean out old files
$dir2=scandir($dir); foreach($dir2 as $f)
{
	if($f{0}=='.' /* || add extra skip conditions here ;-)*/ ) continue;
	if(intval(str_replace('-','',substr($f,0,strpos($f,'.'))))<$l) unlink($dir.$f);
}
?>
