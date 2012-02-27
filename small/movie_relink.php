<?php

$base_dir   = '/mnt/marx/Filme_sortiert';
$genres_dir = $base_dir.'/linked_genres';
$years_dir  = $base_dir.'/linked_years';
$langs_dir  = $base_dir.'/linked_lang';
$all_dir    = $base_dir.'/linked_all';

if(! is_dir($genres_dir)) mkdir($genres_dir);
if(! is_dir($years_dir))  mkdir($years_dir);
if(! is_dir($langs_dir))  mkdir($langs_dir);
if(! is_dir($all_dir))    mkdir($all_dir);

$db = mysql_connect('localhost', 'imdb') or die('mysql connection failed: '.mysql_error());
mysql_select_db('imdb');

exec('find "'.$base_dir.'" -type l -delete');

// select title.id,fsname,info from zuordnungen left join title on (zuordnungen.movie_id = title.id) left join movie_info on (zuordnungen.movie_id = movie_info.movie_id) where fsname sounds like title and info_type_id=3;

$res = mysql_query('SELECT id,dir FROM zuordnungen LEFT JOIN title ON (zuordnungen.movie_id = title.id)') or die(mysql_error()."\n"); // fsname SOUNDS LIKE title
while($M = mysql_fetch_assoc($res))
{
	$dir_name = basename($M['dir']);
	$rel_path = '..'.substr($M['dir'], strlen('/mnt/marx/Filme_sortiert'));
	
	// echo "cd \"$all_dir\"; ln -s \"$rel_path\" \"$dir_name\"\n";
	exec('cd "'.$all_dir.'"; ln -s "'.$rel_path.'" "'.$dir_name.'"');
	
	$rel_path = '../'.$rel_path;
	
	$res2 = mysql_query('SELECT lang FROM zuordnungen_lang WHERE movie_id='.$M['id']);
	if($res2) while($L = mysql_fetch_assoc($res2))
	{
		$lang = $L['lang'];
		$lang_dir = $langs_dir.'/'.$lang;
		if(! is_dir($lang_dir)) mkdir($lang_dir);
		// echo "cd \"$lang_dir\"; ln -s \"$rel_path\" \"$dir_name\"\n";
		exec('cd "'.$lang_dir.'"; ln -s "'.$rel_path.'" "'.$dir_name.'"');
	}
	
	if($M['id'] > 0)
	{
		$res2 = mysql_query('SELECT info AS genre FROM movie_info WHERE info_type_id = 3 AND movie_id='.$M['id']) or die(mysql_error()."\n");
		if($res2) while($G = mysql_fetch_assoc($res2))
		{
			$genre = $G['genre'];
			$genre_dir = $genres_dir.'/'.$genre;
			if(! is_dir($genre_dir)) mkdir($genre_dir);
			// echo "cd \"$genre_dir\"; ln -s \"$rel_path\" \"$dir_name\"\n";
			exec('cd "'.$genre_dir.'"; ln -s "'.$rel_path.'" "'.$dir_name.'"');
		}
		
		$res2 = mysql_query('SELECT MIN(SUBSTRING(info,LENGTH(info)-3)) AS year FROM movie_info WHERE info_type_id = 16 AND movie_id='.$M['id']) or die(mysql_error()."\n");
		if($res2) while($Y = mysql_fetch_assoc($res2))
		{
			$year = $Y['year'];
			if(! empty($year) )
			{
				$year_dir = $years_dir.'/'.$year;
				if(! is_dir($year_dir)) mkdir($year_dir);
				// echo "cd \"$year_dir\"; ln -s \"$rel_path\" \"$dir_name\"\n";
				exec('cd "'.$year_dir.'"; ln -s "'.$rel_path.'" "'.$dir_name.'"');
			}
		}
	}
}

mysql_close($db);

// workaround, TODO: find out why recursive links occur
exec('find "'.$base_dir.'/mit_de" -type l -delete');
exec('find "'.$base_dir.'/ohne_de" -type l -delete');

system('find "'.$base_dir.'"/linked_* -type d -empty -delete');

?>
