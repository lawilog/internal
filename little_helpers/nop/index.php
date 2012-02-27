<?php
error_reporting(E_ALL);

$vaildIP='0123456789.';
$vaildName='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-';
$comps=array();
$fp=fopen('/etc/hosts', 'r');
while(!feof($fp))
{
	$line=fgets($fp);
	if($line{0}=='#') continue;
	while(strpos($line,'  ')!==false) $line=str_replace('  ', ' ', $line);
	$b=0; $name=''; $ip='';
	for($i=0; $i<strlen($line); ++$i)
	{
		if($b==0)
		{
			if(false===strpos($vaildIP, $line{$i})) $b=1;
			else $ip.=$line{$i};
		}
		else
		{
			if(false===strpos($vaildName, $line{$i})) break;
			else $name.=$line{$i};
		}
	}
	if(!empty($ip) && !in_array($ip,array_keys($comps))) $comps[$ip]=$name;
}
fclose($fp);

if(!empty($_REQUEST['ping']) && in_array($_REQUEST['ping'], $comps))
{
	if(empty($_REQUEST['ping'])) exit;
	$ping=shell_exec('ping -c 1 -W 1 -q '.$_REQUEST['ping']);
	$ping=explode("\n", $ping);
	$ping=explode(',',$ping[3]);
	echo 'document.getElementById("'.$_REQUEST['ping'].'").color="'.(intval($ping[1])?'green':'grey').'";';
	exit;
}
?>
<html>
 <head>
  <title>Manifest</title>
  <style><!--
  body {font-family:Verdana; font-size:12pt; background-color:navy; color:white;}
  --></style>
 </head>
<body><h2>Ein Gespenst geht um im Netzwerk - das Gespenst eines WG-Servers.</h2>
<h3>Die Geschichte aller bisherigen Server ist die Geschichte von Speicherknappheit.</h3>
<hr/>
<?php
echo '<pre>'; system('df -h'); echo '</pre>';

$script='';
$erg=array();
foreach($comps as $ip=>$name)
{
	if(empty($name)) continue;
	$erg[]='<font color="yellow" id="'.$name.'" name="'.$name.'">'.$name.' ('.$ip.')</font>';
	$script.='<script src="#?ping='.$name.'"></script>';
}
echo '<b>'.implode($erg,'</b> - <b>').'</b>';
?>
<hr/><h3>Daten aller Nutzer vereinigt euch!</h3>
<?php echo $script; ?>
</body></html>
