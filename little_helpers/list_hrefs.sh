#!/bin/bash
url="$1"
wget "$url" -O - -o /dev/null | grep_hrefs.sh
