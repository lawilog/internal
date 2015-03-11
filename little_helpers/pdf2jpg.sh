#!/bin/bash
for f in ${@}
do
	convert -trim -density 300 -scale 1280 -quality 90 $f ${f/.pdf/.jpg}
done
