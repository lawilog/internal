#!/bin/bash
pdb_file="$1"
xyzti_file=$(tempfile)
ij_file=$(tempfile)

declare -A rs
rs[default]=0.5
rs[H]=0.2
rs[NA]=0.6
rs[CL]=0.8

cat <<!
\definecolor{H}{RGB}{180,180,180}
\definecolor{C}{RGB}{64,64,64}
\definecolor{N}{RGB}{127,255,127}
\definecolor{O}{RGB}{127,127,255}
\definecolor{NA}{RGB}{127,255,127}
\definecolor{SI}{RGB}{127,127,127}
\definecolor{S}{RGB}{255,255,127}
\definecolor{P}{RGB}{127,200,200}
\definecolor{CL}{RGB}{100,200,100}
!EOF

egrep '^ATOM|^HETATM' "$pdb_file" | awk '{print $6, $7, $8, $3, $2}' | sort -n -k3 > "$xyzti_file"
cat "$xyzti_file" | while read x y z type id
do
	u=$x
	v=$y
	type="${type^^}" # uppercase
	r=$( [ ${rs[$type]+_} ] && echo ${rs[$type]} || echo ${rs[default]} )
	echo "\\shade[ball color=$type] ($u,$v) circle ($r);"
done

rm "$xyzti_file" "$ij_file"
