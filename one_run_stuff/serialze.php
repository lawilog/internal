<?php
$a=array(
'baseurl' => '/Intraliro/',
'basedir' => 'w:/www/Intraliro/',
'mysql_host' => 'localhost',
'mysql_user' => 'root',
'mysql_psw' => 'root',
'db_name' => 'masc',
'SchulName' => 'Gymnasium Alexander von Humboldt',
'KBeg' => 5,
'KEnd' => 12,
'aktJahr' => 2006
);
echo serialize($a);
?>