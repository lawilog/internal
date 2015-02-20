#!/bin/bash
echo "  Device   Temp        Status LoadCycles Health"
for dev in /dev/sd?
do
	echo "$dev $(smartctl -A $dev | grep Temp | awk '{printf(" %i °C ",  $10)}') $(hdparm -C $dev | awk '/state/{printf("%12s", $NF)}') $(smartctl -A $dev | awk '/Load_Cycle_Count/{printf("%10i", $NF)}') $(smartctl -H $dev | egrep -v '^$|smartctl|Copyright|START')"
done
