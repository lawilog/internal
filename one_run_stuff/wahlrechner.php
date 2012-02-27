<?php
// input
$krit=0.5;
$part=array('cducsu', 'spd', 'gruen', 'fdp', 'linke');
$wahl=array(30,       18,    6,       7,     27);
//$wahl=array( 35,       24,    10,      13,    12    );
//$wahl=array( 38.5,     38.5,  8.6,      7.4,    5   );

// postprocess input
$koal=array();
$n=count($wahl);
$sum=array_sum($wahl); for($i=0; $i<$n; ++$i) $wahl[$i]=$wahl[$i]/$sum;
//for($i=0; $i<$n; ++$i) $wahl[$i]=$wahl[$i]/100;

// go
for($i=0; $i<$n; ++$i) if($wahl[$i]>=$krit) $koal[$i]=array($i);
for($i=0; $i<$n; ++$i)
{
	for($j=$i+1; $j<$n; ++$j)
	{
		for($k=$j+1; $k<$n; ++$k)
		{
			$proz=$wahl[$i]+$wahl[$j]+$wahl[$k];
			echo $part[$i]."\t".$part[$j]."\t".$part[$k]."\t".(intval(1000*$proz)/10)."%\n";
			if($proz>=$krit)
			{
				if($wahl[$i]+$wahl[$j]>=$krit) {$sig=$n*$i+$j; if(!in_array($sig,array_keys($koal))) $koal[$sig]=array($i,$j); continue;}
				if($wahl[$i]+$wahl[$k]>=$krit) {$sig=$n*$i+$k; if(!in_array($sig,array_keys($koal))) $koal[$sig]=array($i,$k); continue;}
				if($wahl[$j]+$wahl[$j]>=$krit) {$sig=$n*$j+$k; if(!in_array($sig,array_keys($koal))) $koal[$sig]=array($j,$k); continue;}
				$koal[$n*$n*$i+$n*$j+$k]=array($i,$j,$k);
			}
		}
	}
}

// output
echo "Moeglich also:\n";
foreach($koal as $a)
{
	$proz=0;
	foreach($a as $i) {$proz+=$wahl[$i]; echo $part[$i]."\t";}
	echo (intval(1000*$proz)/10)."%\n";
}
?>
