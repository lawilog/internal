#!/bin/bash
mediainfo "$1" | awk '/Width/{gsub(/(.*: | |pixels)/, "", $0); W=1*$0} /Height/{gsub(/(.*: | |pixels)/, "", $0); H=1*$0} END{R=""; if(W && H) {if(W<640) R="low quali"; if(W>=640 || H>=480) R="480p"; if(H>=576) R="576p"; if(W>=1280 || H>=720) R="720p"; if(W>=1920 || H>=1080) R="1080p"}; print R}'
