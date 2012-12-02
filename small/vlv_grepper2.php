<?php
function html2utf8($x) {return trim(html_entity_decode($x, ENT_QUOTES, 'UTF-8'));}

$VLV_URL = 'http://www.tu-ilmenau.de/vlv/index.php?id=330'; // 'http://www.tu-ilmenau.de/vlv/index.php?id=6';
$TABLE_NAME = 'vlv_ws10';

mysql_connect('localhost', 'vlv');
mysql_select_db('vlv');
mysql_set_charset('utf8');
mysql_query('DROP TABLE IF EXISTS '.$TABLE_NAME);
mysql_query('CREATE TABLE '.$TABLE_NAME.' (id INT PRIMARY KEY AUTO_INCREMENT, fach TEXT, typ TEXT, dozent TEXT, wtag VARCHAR(16), zeitraum TEXT, uhrzeit VARCHAR(32), raum TEXT, zielgruppe TEXT, update_time VARCHAR(16))');

$html = file_get_contents($VLV_URL);
$studiengang_urls = array();
$p = 0;
while(($p = strpos($html, 'href="index.php?id=330&funccall=1&', $p)) !== false) // ### id=
{
	$p += 6;
	$p2 = strpos($html, '">', $p);
	$url = substr($html, $p, $p2-$p);
	if(strpos($url, '&amp;fs=') === false) $studiengang_urls[] = html_entity_decode($url);
	$p = $p2;
}
//print_r($studiengang_urls);
$vlv = array(); // [fach][typ] = (0 => dozent, 1 => wochentag, 2 => zeitraum, 3 => uhrzeit, 4 => raum, 5 => zielgruppe, 6 => aenderungsdatum)
foreach($studiengang_urls as $studiengang_url)
{
	//$studiengang_url = $studiengang_urls[1];
	$html = file_get_contents('http://www.tu-ilmenau.de/vlv/'.$studiengang_url);
	echo "$studiengang_url\n";
	//echo "$html\n";
	$p = strpos($html, 'Liste der Veranstaltungen');
	while(($p = strpos($html, '<td colspan=7><b>', $p)) !== false)
	{
		$p += 17;
		$p2 = strpos($html, '<', $p);
		$fach = html2utf8(substr($html, $p, $p2-$p));
		echo "Fach \"$fach\" ";
		
		$dozent = '';
		$p = strpos($html, '<td colspan=6>', $p);
		if($p !== false)
		{
			$p += 14;
			$p2 = strpos($html, '</td>', $p);
			$dozent = str_replace('Lesende(r): ', '', html2utf8(substr($html, $p, $p2-$p)));
		}
		$p = $p2; // either above or current
		//echo "Dozent \"$dozent\" ";
		
		$typ = '';
		//$p = strpos($html, '<tbody>', $p); if($p === false) break;
		$p_end = strpos($html, '</table>', $p);
		while(($p = strpos($html, '<tr valign=top>', $p)) !== false && $p < $p_end)
		{
			$p_end2 = strpos($html, '</tr>', $p);
			$info = array();
			while(($p = strpos($html, '<td', $p)) !== false && $p < $p_end2)
			{
				$p = strpos($html, '>', $p) + 1;
				$p2 = strpos($html, '<', $p);
				if($p === false || $p2 === false) {$p = $p_end; break;}
				$info[] = str_replace('Geändert am: ', '', html2utf8(substr($html, $p, $p2-$p)));
				$p = $p2;
			}
			$p = $p_end2;
			//echo "\n\t(".implode(', ', $info).') ';
			/*if(count($info) != 7) {
				echo ' leaving 1 ';
				$info = array($info[0], $info[2], $info[3], $info[4], $info[5], $info[6], $info[7]);
			}*/
			if((!empty($info[0])) && $info[0] != ' ') $typ = trim(str_replace(':', '', $info[0]));
			$info[0] = $dozent;
			//echo ' $typ = "'.$typ.'" $info[0] = "'.$info[0].'"';
			if(empty($vlv[$fach][$typ])) $vlv[$fach][$typ][] = $info;
			else
			{
				$b = true;
				foreach($vlv[$fach][$typ] as $k => $v)
				{
					if($v[0] == $info[0] && $v[1] == $info[1] && $v[2] == $info[2] && $v[3] == $info[3] && $v[4] == $info[4])
					{
						$b = false;
						$vlv[$fach][$typ][$k][5] .= ', '.$info[5];
						break;
					}
				}
				if($b) $vlv[$fach][$typ][] = $info;
			}
			//echo "\np (end of loop) = $p\n";
			if($p === false) break;
		}
		
		$p = $p_end;
		if($p === false) break;
		echo "\n";
	}
}
foreach($vlv as $fach => $a) // [fach][typ] = (0 => dozent, 1 => wochentag, 2 => zeitraum, 3 => uhrzeit, 4 => raum, 5 => zielgruppe, 6 => aenderungsdatum)
{
	foreach($a as $typ => $b)
	{
		foreach($b as $info)
		{
			mysql_query("INSERT INTO $TABLE_NAME (fach, typ, dozent, wtag, zeitraum, uhrzeit, raum, zielgruppe, update_time) VALUES ('".
				mysql_real_escape_string($fach)."', '".
				mysql_real_escape_string($typ)."', '".
				mysql_real_escape_string($info[0])."', '".
				mysql_real_escape_string($info[1])."', '".
				mysql_real_escape_string($info[2])."', '".
				mysql_real_escape_string($info[3])."', '".
				mysql_real_escape_string($info[4])."', '".
				mysql_real_escape_string($info[5])."', '".
				mysql_real_escape_string($info[6])."')");
		}
	}
}
?>
