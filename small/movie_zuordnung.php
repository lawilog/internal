<?php
/* TODO:
- webinterface for correction - corrections should stay permanent
- manually check and maybe rename "guesses" and "no idea" titles - or find a better way to match them automatically
*/

function debug($str) {echo $str;}

function add2list($dir, &$list) // creates $dirs in arrays of [0 => path, 1 => movie title from folder name, 2 => array of languages, 3 => year]
{
	$items = scandir($dir);
	foreach($items as $item)
	{
		if($item == '.' || $item == '..') continue;
		$path = $dir.'/'.$item;
		if(! is_dir($path)) continue;
		
		$lang = array();
		$pos = strpos($item, '(');
		if($pos !== false)
		{
			$lang = explode(',', substr($item, $pos+1, strpos($item, ')', $pos)-$pos-1));
			foreach($lang as $k=>$v) $lang[$k] = trim($v);
			$item = substr($item, 0, $pos);
		}
		
		$pos = strpos($item, '--'); if($pos !== false) $item = substr($item, 0, $pos);
		
		$year = 0;
		$pos = strpos($item, '[');
		if($pos !== false)
		{
			$year = intval(substr($item, $pos+1, strpos($item, ']', $pos)-$pos-1));
			$item = substr($item, 0, $pos);
		}
		
		if(strpos($item, ',') === false) $list[] = array($path, trim($item), $lang, $year);
		else add2list($path, $list);
	}
}

function AlphaNum($str) // remove all characters which are note letters or numbers
{
	$allow=html_entity_decode
	(
		'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'. '&Auml;&Ouml;&Uuml;&auml;&ouml;&uuml;&szlig;&Agrave;&Aacute;&Acirc;&Atilde;&Aring;&Ccedil;&Egrave;&Eacute;&Ecirc;&Euml;&Igrave;&Iacute;&Icirc;&Iuml;&Ntilde;&Ograve;&Oacute;&Ocirc;&Otilde;&Ugrave;&Uacute;&Ucirc;&Yacute;&agrave;&aacute;&acirc;&atilde;&aring;&ccedil;&egrave;&eacute;&ecirc;&euml;&igrave;&iacute;&icirc;&iuml;&ntilde;&ograve;&oacute;&ocirc;&otilde;&ugrave;&uacute;&ucirc;&yacute;&yuml;',
		ENT_QUOTES,
		'UTF-8'
	);
	$newstr=''; $len=strlen($str);
	for($i=0; $i<$len; $i++)
	{
		if(strrpos($allow, $str[$i])!==false) $newstr.=$str[$i];
	}
	return $newstr;
}

function find_movie($title, $year, $be_less_acurate) // returns array($exact_match, $best_matching_found = array($movie_id, $aka_id))
{
	$where = "(kind_id=1 OR kind_id=3 OR kind_id=4)";
	if(empty($year)) $where.=' AND (production_year IS NULL OR (production_year>1960 AND production_year<'.(date('Y')+2).'))';
	else             $where.=' AND (production_year IS NULL OR production_year='.$year.')';
	$sql_std = array(
		"SELECT id AS movie_id,title,0 AS aka_id FROM title WHERE $where AND ",
		"SELECT movie_id,title,id AS aka_id FROM aka_title WHERE $where AND note LIKE '%German%' AND ",
		"SELECT movie_id,title,id AS aka_id FROM aka_title WHERE $where AND "
	);
	
	$best_matching_found = false;
	
	while(true)
	{
		$mode = ($be_less_acurate?"guess-mode" : "normal-mode");
		debug("now trying \"$title\" ($mode)...\n");
		if(! $be_less_acurate)
		{
			$sqls = array();
			foreach($sql_std as $s) $sqls[] = $s."title LIKE '$title';";
			foreach($sql_std as $s) $sqls[] = $s."title LIKE '$title%';";
			foreach($sql_std as $s) $sqls[] = $s."title LIKE '%$title%';";
			
			foreach($sqls as $sql)
			{
				$res = mysql_query($sql) or die("FAILED: $sql\n".mysql_error()."\n");
				debug("$sql\n");
				if(! ($num_rows = mysql_num_rows($res))) continue;
				$row = mysql_fetch_assoc($res);
				debug("($mode exact) $num_rows results (first: \"".$row['title']."\")\n");
				if(! $best_matching_found) // ambigious match, remember first hit
					$best_matching_found = array($row['movie_id'], $row['aka_id']);
				if($num_rows == 1) // try to find exact match
					return array(true, array($row['movie_id'], $row['aka_id']));
			}
		}
		
		// try to remove " 1" ("American Pie 1" -> "American Pie")
		if(substr($title, -2)==' 1') {$title = substr($title, 0, strlen($title)-2); continue;}
		
		// check for phonetic similiar movies
		$AlphaNum_title = strtolower(AlphaNum($title));
		$sqls = array();
		foreach($sql_std as $s) $sqls[] = $s."title SOUNDS LIKE '$title';";
		foreach($sqls as $sql)
		{
			$res = mysql_query($sql) or die("FAILED: $sql\n".mysql_error()."\n");
			debug("$sql\n");
			if(! ($num_rows = mysql_num_rows($res))) continue;
			$M = mysql_fetch_assoc($res);
			debug("(phonetic) $num_rows results (first: \"".$row['title']."\")\n");
			
			if($be_less_acurate && $num_rows == 1) // we should be less acurate and found one movie that sounded like ours
			{
				$pro; similar_text(strtolower(AlphaNum($M['title'])), $AlphaNum_title, $pro);
				if($pro >= 66) return array(false, array($M['movie_id'], $M['aka_id'])); // similarity at least 66%
			}
			$match_count = 0; $match_id = array(0, 0);
			do
			{
				if(strtolower(AlphaNum($M['title'])) == $AlphaNum_title)
				{
					++$match_count;
					$match_id = array($M['movie_id'], $M['aka_id']);
					if(! $best_matching_found) $best_matching_found = $match_id;
					debug("($mode phonetic) had good match: \"".$M['title']."\", makes $match_count matches\n");
				}
			} while($M = mysql_fetch_assoc($res));
			if($match_count == 1) // only non-letters had prohibited exact match
				return array(true, $match_id);
		}
		
		break;
	}
	
	if(strpos($title, ' - ') !== false) // split on ' - ' and try all combinations
	{
		debug("splitting\n");
		$parts = explode(' - ', $title);
		$n = count($parts);

		for($i = pow(2, $n) - 1; $i > 0; --$i)
		{
			$bin = array(); 
			for($j = 0, $k = $i; $j <= $n; ++$j) $k = ($k - ($bin[$j] = $k % 2)) / 2;
			$comb_title = array();
			foreach($bin as $j=>$b) if($b) $comb_title[] = $parts[$j];
			list($inner_exact, $inner_best_matching_found) = find_movie(implode('%', $comb_title), $year, $be_less_acurate); // recursion
			if($inner_exact) return array(true, $inner_best_matching_found);
			if($inner_best_matching_found && ! $best_matching_found) $best_matching_found = $inner_best_matching_found;
		}
	}
	
	return array(false, $best_matching_found);
}

$movie_dirs = array('/mnt/marx/Filme_sortiert/mit_de', '/mnt/marx/Filme_sortiert/ohne_de');
// $movie_dirs = array('/mnt/marx/Filme_sortiert/mit_de/Der Herr der Ringe 1,2,3 (de,en)/', '/mnt/marx/Filme_sortiert/mit_de/Star Wars, Saga (de,en)/');
// $movie_dirs = array('/mnt/marx/Filme_sortiert/mit_de/Matrix 1,2,3,Animatrix,Roots (de,en)/');

$dirs = array();
foreach($movie_dirs as $dir) add2list($dir, $dirs);

$db = mysql_connect('localhost', 'imdb') or die('mysql connection failed: '.mysql_error());
mysql_select_db('imdb');

$tables = array();
$res = mysql_list_tables('imdb');
while($row = mysql_fetch_row($res)) $tables[] = $row[0];
mysql_free_result($res);

// mysql_query('DROP TABLE IF EXISTS zuordnungen;') or die(mysql_error()."\n");
// mysql_query('DROP TABLE IF EXISTS zuordnungen_lang;') or die(mysql_error()."\n");

if(in_array('zuordnungen', $tables))
{
	$res = mysql_query('SELECT MIN(movie_id) AS neg FROM zuordnungen');
	$neg = mysql_result($res, 0) - 2;
	
	$already_matched = array();
	$res = mysql_query('SELECT dir FROM zuordnungen WHERE confirmed IS TRUE');
	while($M = mysql_fetch_assoc($res)) $already_matched[] = $M['dir'];
	mysql_free_result($res);
}
else
{
	$neg = -1;
	$already_matched = array();
	mysql_query('CREATE TABLE zuordnungen (movie_id INT, aka_id INT, fsname TEXT, dir TEXT, confirmed BOOL DEFAULT FALSE);') or die(mysql_error()."\n");
}

if(! in_array('zuordnungen_lang', $tables)) mysql_query('CREATE TABLE zuordnungen_lang (movie_id INT, lang VARCHAR(8));') or die(mysql_error()."\n");

$new_matches = array();
$no_idea = array();

foreach($dirs as $i=>$movie)
{
	if(in_array($movie[0], $already_matched)) continue; // check if $dir = $movie[0] already matched in previous run
	
	$title = mysql_real_escape_string($movie[1]);
	list($exact_match, $best_matching_found) = find_movie($title, $movie[3], false);
	
	$keyword = '';
	if($exact_match)
	{
		$keyword = 'STATUS MATCHED';
		$new_matches[$i] = $best_matching_found;
	}
	else
	{
		// retry in wild guess mode
		if(! $best_matching_found) list($exact_match, $best_matching_found) = find_movie($title, $movie[3], true);
		
		if($best_matching_found)
		{
			$keyword = 'STATUS GUESSED';
			$new_matches[$i] = $best_matching_found;
		}
		else
		{
			$keyword = 'STATUS NO IDEA';
			$no_idea[] = $i;
		}
	}
	
	echo "$keyword:\t\"".$movie[1]."\"\n";
}

echo "match found for ".count($new_matches)." out of ".count($dirs)."\n";
echo "no idea for ".count($no_idea)." movies:\n";
foreach($no_idea as $i) echo $dirs[$i][1]."\n";

echo "\nentering into DB...\n";

foreach($new_matches as $i=>$movie_ids)
{
	$movie = $dirs[$i];
	list($movie_id, $aka_id) = $movie_ids;
	$dir = mysql_real_escape_string($movie[0]);
	mysql_query("DELETE FROM zuordnungen WHERE dir='$dir'");
	mysql_query("INSERT INTO zuordnungen (movie_id, aka_id, fsname, dir) VALUES ($movie_id, $aka_id, '".mysql_real_escape_string($movie[1])."', '$dir');");
	foreach($movie[2] as $lang) mysql_query("INSERT INTO zuordnungen_lang (movie_id, lang) VALUES ($movie_id, '$lang');");
}

foreach($no_idea as $i)
{
	$movie = $dirs[$i];
	mysql_query("INSERT INTO zuordnungen (movie_id, aka_id, fsname, dir) VALUES ($neg, 0, '".mysql_real_escape_string($movie[1])."', '".mysql_real_escape_string($movie[0])."');");
	foreach($dirs[$i][2] as $lang) mysql_query("INSERT INTO zuordnungen_lang (movie_id, lang) VALUES ($neg, '$lang');");
	--$neg;
}


mysql_close($db);

echo "all done :-)\n";

?>
