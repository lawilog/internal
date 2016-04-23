#!/bin/bash
src="$1"
dst=$(cd "$2" && pwd) || exit
cd "$src" || exit
find -type d -exec mkdir -p "$dst"/{} \;
find ! -type d -exec mv -i {} "$dst"/{} \;
while [ $(find -type d -empty | wc -l) -gt 1 ]; do find -type d -empty -delete; done 2>/dev/null
rmdir "$(pwd)"
