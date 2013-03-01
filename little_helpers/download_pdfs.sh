#!/bin/bash
url="$1"
wget "$url" -O - -o /dev/null | grep_hrefs | grep -i '.pdf$' | url_combine.sh "$url" | while read pdfurl; do wget "$pdfurl"; done
