#!/bin/bash
echo $(( $(date -d "$2" +%s) - $(date -d "$1" +%s) )) | s2h.sh
