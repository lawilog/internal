#!/bin/bash
# export HOME="/home/alphakevin"
xhost +local:root
#gksudo -u alphakevin env PULSE_LATENCY_MSEC=60 skype &
kdesudo -u alphakevin env PULSE_LATENCY_MSEC=60 skype &
