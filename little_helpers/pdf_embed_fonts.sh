#!/bin/bash
fin="${1}"
fout="embedded_$fin"
echo "$fin --> $fout"
gs -q -dNOPAUSE -dBATCH -dPDFSETTINGS=/prepress -sDEVICE=pdfwrite -sOutputFile="$fout" "$fin"
