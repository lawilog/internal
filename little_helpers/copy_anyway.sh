#!/bin/bash
inf="$1"
outf="$2"
dd if="$inf" of="$outf" bs=4k conv=noerror,sync
truncate --reference "$inf" "$outf"
