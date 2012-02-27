#!/bin/bash
echo -en "will copy header\n from: $1\n to  : $2\nPress any key to continue..."
read x
dd if=$1 of=$2 count=1 bs=20 conv=notrunc
# maybe even 28 ?
# 7 magic bytes
