<?php
function decodeSize( $bytes )
{
	$types = array( 'B', 'KB', 'MB', 'GB', 'TB' );
	for( $i = 0; $bytes >= 1024 && $i < ( count( $types ) -1 ); $bytes /= 1024, $i++ );
	return( round( $bytes, 2 ) . " " . $types[$i] );
}
function cmp($d0, $d1)
{
	if($d0[2]==$d1[2]) return strcmp($d0[0], $d1[0]);
	else return ($d0[2] < $d1[2]) ? -1 : 1;
}
exec('mount | grep -v bind | while read a b c d; do echo $c; done', $disks);
print_r($disks);
$fs = array();
$max_total_space = 0;
foreach($disks as $disk)
{
	if(substr($disk, 0, 5) == '/proc' || in_array($disk, array('/dev', '/dev/pts', '/sys'))) continue;
	$total_space = disk_total_space($disk);
	if($total_space > $max_total_space) $max_total_space = $total_space;
	$fs[]=array($disk, disk_free_space($disk), $total_space);
}
usort($fs, 'cmp');
print_r($fs);
echo '<table border="0"><tr><th>Filesystem</th><th rowspan="2">Space</th><th>Used</th></tr>';
foreach($fs as $d)
{
	echo '<tr><td>'.$d[0].'</td><td>GIF</td><td>'.decodeSize($d[2]).'</td><td>'.decodeSize($d[1]).' used ('.intval(100*$d[1]/$d[2]).'%)</td></tr>';
}
echo '</table>';
?>
