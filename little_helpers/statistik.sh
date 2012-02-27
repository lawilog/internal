#!/bin/bash
tmpfile="`/bin/tempfile`"
while read x; do echo "${x}" >> ${tmpfile}; done
echo -e "A=load('$tmpfile'); min=min(A)\n max=max(A)\n mean=mean(A)\n stddev=std(A)\n" | octave -q
