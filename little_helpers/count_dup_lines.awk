#!/usr/bin/awk -f
BEGIN{b=1} {if(b) {b=0; m=1; s=$0} else {if($0==s) ++m; else {printf("%6i %s\n", m, s); m=1; s=$0}}} END{printf("%6i %s\n", m, s)}
