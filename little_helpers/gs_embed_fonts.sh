#!/bin/bash
inf="$1"
outf="${2:-embedded_$1}"
echo "$inf --> $outf"
gs -q -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile="$inf" -dPDFSETTINGS=/prepress -dEmbedAllFonts=true -dSubsetFonts=true -dCompatibilityLevel=1.6 "$outf"
