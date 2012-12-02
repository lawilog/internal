#!/bin/bash
touchpad_id=$( xinput list | grep Synaptics | sed 's/.*id=//g' | awk '{print $1}' )
xinput set-prop $touchpad_id "Device Enabled" $( xinput list-props $touchpad_id | grep "Device Enabled" | awk '{print !$NF}' )
