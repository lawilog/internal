#!/usr/bin/php
<?php
$file='/home/lawilog/proggen/little_helpers/bibo.txt';
$host='katalog.bibliothek.tu-ilmenau.de';//'ilmopc4.bibliothek.tu-ilmenau.de';
$port=80;//8080;
$url='/loan/DB=1/SET=1/TTL=1/USERINFO';
$PostData='&HOST_NAME='.
	'&HOST_PORT='.
	'&HOST_SCRIPT='.
	'&&LOGIN=KNOWNUSER'.
	'&STATUS=HML_OK'.
	'&BOR_U=340000049252'.
	'&BOR_PW=cefadroxil';
$resp=array();
$actions=array('UI_DATA','UI_LOL','UI_LOR','UI_LOC');//,'UI_CHUPW'
foreach($actions as $i=>$act)
{
	$requ='ACT='.$act.$PostData;
	$resp[$i]='';
	$fp=fsockopen($host,$port) or die('! socket');
	$post="POST $url HTTP/1.1\r\n".
	"Host: $host\r\n".
	"Connection: close\r\n".
	"Content-Type: application/x-www-form-urlencoded\r\n".
	"Content-Length: ".strlen($requ)."\r\n\r\n".
	$requ."\r\n";
	fputs($fp,$post);
	while(! feof($fp)) $resp[$i].=fgets($fp,1024);
	fclose($fp);
}
// quick & dirty
$infos=array();
$pos=strpos($resp[0],'<form');
$text=substr($resp[0],$pos,strpos($resp[0],'</form')-$pos);
while(($pos=strpos($text,'preslabel'))!==false)
{
	$pos2=strpos($text,'>',$pos);
	$tag=html_entity_decode(substr($text,$pos2+7,strpos($text,'<',$pos2)-$pos2-8));
	$text=substr($text,$pos2);
	$pos2=strpos($text,'presvalue');
	$pos2=strpos($text,'>',$pos2);
	$infos['user_data'][$tag]=html_entity_decode(substr($text,$pos2+1,strpos($text,'<',$pos2)-$pos2-1));
	//$text=substr($text,$pos2);
}

$text=substr($resp[1],strpos($resp[1],'list of loans - data'));
$pos=strpos($text,'checkbox');
$text=substr($text,$pos);
while(($pos=strpos($text,'<td class="plain">'))!==false)
{
	$pos2=strpos($text,'>',$pos+2);
	$infos['loans'][]=array();
	$i=count($infos['loans'])-1;
	$infos['loans'][$i][]=html_entity_decode(substr($text,$pos2+1,strpos($text,'<',$pos2)-$pos2-1));
	$subtext=substr($text,$pos2+1,strpos($text,'</tr>',$pos2)-$pos2-1);
	while(($pos=strpos($subtext,'<td class="value-small">'))!==false)
	{
		$pos3=strpos($subtext,'>',$pos+2);
		$infos['loans'][$i][]=html_entity_decode(substr($subtext,$pos3+1,strpos($subtext,'<',$pos3)-$pos3-1));
		$subtext=substr($subtext,$pos3);
	}
	$text=substr($text,$pos2);
}

$text=substr($resp[2],strpos($resp[2],'list of reservations - data'));
//echo '<pre style="color:red">'.htmlentities($text).'</pre>';
$pos=strpos($text,'checkbox');
$text=substr($text,$pos);
//echo '<pre style="color:blue">'.htmlentities($text).'</pre>';
while(($pos=strpos($text,'<td class="plain">'))!==false)
{
	$pos2=strpos($text,'>',$pos+2);
	$infos['reservations'][]=array();
	$i=count($infos['reservations'])-1;
	$infos['reservations'][$i][]=html_entity_decode(substr($text,$pos2+1,strpos($text,'<',$pos2)-$pos2-1));
	$subtext=substr($text,$pos2+1,strpos($text,'</tr>',$pos2)-$pos2-1);
	while(($pos=strpos($subtext,'<td class="value-small">'))!==false)
	{
		$pos3=strpos($subtext,'>',$pos+2);
		$infos['reservations'][$i][]=html_entity_decode(substr($subtext,$pos3+1,strpos($subtext,'<',$pos3)-$pos3-1));
		$subtext=substr($subtext,$pos3);
	}
	$text=substr($text,$pos2);
}
$infos['debts']=(strpos($resp[3],'No outstanding debts.')===false)?'yes':'no';
if(! $oldinfo=@ file_get_contents($file)) $oldinfo=$infos;
else $oldinfo=unserialize($oldinfo);
file_put_contents($file,serialize($infos));
$chances=array();
foreach($infos['loans'] as $i=>$loan)
{
	$d=explode('-',$loan[4]);
	if(intval($d[2].$d[1].$d[0])<= intval(date('Ymd')) || date('d-m-Y',strtotime('+1 day'))==$loan[4] || date('d-m-Y',strtotime('+2 day'))==$loan[4] || date('d-m-Y',strtotime('+3 day'))==$loan[4])
	{
		$chances[]="# folgendes Buch muss bald zurueck gegeben werden:\n".$loan[0]."\n".$loan[1]."\n".$loan[2]."\nausgeliehen bis: ".$loan[4];
	}
	$found=false;
	foreach($oldinfo['loans'] as $j=>$oldloan)
	{
		if($loan[0]==$oldloan[0]) {$found=true; break;}
	}
	if(!$found)
	{
		$chances[]="# neues Buch ausgeliehen:\n".$loan[0]."\n".$loan[1]."\n".$loan[2]."\nausgeliehen bis: ".$loan[4];
	}
}
foreach($oldinfo['loans'] as $i=>$oldloan)
{
	$found=false;
	foreach($infos['loans'] as $j=>$loan)
	{
		if($loan[0]==$oldloan[0]) {$found=true; break;}
	}
	if(!$found)
	{
		$chances[]="# Buch nicht mehr ausgeliehen:\n".$oldloan[0]."\n".$oldloan[1]."\n".$oldloan[2]."\nausgeliehen bis: ".$oldloan[4];
	}
}
foreach($infos['reservations'] as $i=>$loan)
{
	$found=false;
	foreach($oldinfo['reservations'] as $j=>$oldloan)
	{
		if($loan[0]==$oldloan[0]) {$found=true; break;}
	}
	if(!$found)
	{
		$chances[]="# neue Reservierung:\n".$loan[0]."\n".$loan[1]."\nwarte seit: ".$loan[4];
	}
}
foreach($oldinfo['reservations'] as $i=>$oldloan)
{
	$found=false;
	foreach($infos['reservations'] as $j=>$loan)
	{
		if($loan[0]==$oldloan[0]) {$found=true; break;}
	}
	if(!$found)
	{
		$chances[]="# Reservierung aufgehoben:\n".$oldloan[0]."\n".$oldloan[1]."\nwarte seit: ".$oldloan[4];
	}
}
if($infos['debts']=='yes') $chances[]="# Ausstehende Schulden.";
echo '<pre>'.print_r($infos,1).'</pre>';
//echo '<pre style="color:blue">'.print_r($oldinfo,1).'</pre>';
//echo '<pre style="color:red">'.htmlentities(implode("\n\n",$chances)).'</pre>';
if(!empty($chances)) system('xmessage "'.implode("\n\n",$chances).'"');
exit(0);
/*

http://ilmopc4.bibliothek.tu-ilmenau.de:8080/loan/DB=1/USERINFO
?ACT=UI_DATA&BOR_U=340000049252&BOR_PW_ENC=NuB36F%2BF5rBCXz8Ml6yOqdRD3U%2BpBk8OBSR5JNU7wy0%3D
User Data

Entleihungen
?ACT=UI_LOL&BOR_U=340000049252&BOR_PW_ENC=NuB36F%2BF5rBCXz8Ml6yOqdRD3U%2BpBk8OVgIdWi%2Bo5q0%3D

Vormerkungen
?ACT=UI_LOR&BOR_U=340000049252&BOR_PW_ENC=NuB36F%2BF5rBCXz8Ml6yOqdRD3U%2BpBk8OVgIdWi%2Bo5q0%3D

Kosten
?ACT=UI_LOC&BOR_U=340000049252&BOR_PW_ENC=NuB36F%2BF5rBCXz8Ml6yOqdRD3U%2BpBk8OVgIdWi%2Bo5q0%3D

Passwort
?ACT=UI_CHUPW&BOR_U=340000049252&BOR_PW_ENC=NuB36F%2BF5rBCXz8Ml6yOqdRD3U%2BpBk8OVgIdWi%2Bo5q0%3D

*/
?>
