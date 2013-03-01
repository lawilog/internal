#!/bin/bash
. ~/.envrc
mem_usage_per_program.sh | gxmessage -title "Memory Usage per Program" -file - -buttons "OK:0" -default OK -font "Courier"
