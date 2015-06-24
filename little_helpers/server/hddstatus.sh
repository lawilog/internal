#!/bin/bash
echo "  Device   Temp        Status LoadCycles  SpinUpRaw,V,W,T ReadErrors ReallocSec Health"
for dev in /dev/sd?
do
	echo "$dev "\
"$(smartctl -A $dev | grep Temp | awk '{printf(" %3i C ",  $10)}') "\
"$(hdparm -C $dev | awk '/state/{printf("%12s", $NF)}') "\
"$(smartctl -A $dev | awk '/Load_Cycle_Count/{printf("%10i", $NF)}') "\
"$(smartctl -A $dev | awk '/Spin_Up_Time/{printf("%5i,%3i,%3i,%2i", $NF, $4, $5, $6)}') "\
"$(smartctl -A $dev | awk '/Raw_Read_Error_Rate/{printf("%10i", $NF)}') "\
"$(smartctl -A $dev | awk '/Reallocated_Sector_Ct/{printf("%10i", $NF)}') "\
"$(smartctl -H $dev | egrep -v '^$|smartctl|Copyright|START')"
done
