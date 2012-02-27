#!/bin/bash
mpg123 -w "$1.wav" "$1"
dvda-author -o DVD -g "$1.wav" -X .
mkisofs -o "$1.iso" -sort sort.txt -udf DVD
