#!/bin/bash
#hddtemp /dev/sd?
for dev in /dev/sd?; do echo -n "$dev "; smartctl -A $dev | grep Temp | awk '{print $NF, "°C"}'; done
