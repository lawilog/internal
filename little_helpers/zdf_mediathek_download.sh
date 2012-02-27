#!/bin/bash
url="$1"
curl "$url" | grep mms: | cut -d\" -f4 | xargs -n1 mplayer -dumpstream -dumpfile "${url##*/}.wmv"
