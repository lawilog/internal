#!/bin/bash
delim="$1"
str="$2"
echo "$str" | awk -F"$delim" "{
	b[NF] = 1;
	for(n=1; n<2^NF; ++n) {
		pre=\"\"
		for(i=1; i<=NF; ++i) {
			if(b[i]) {
				printf(\"%s%s\", pre, \$i);
				pre=FS
			}
		}
		printf(\"\\n\");

		k = NF; while(++b[k] == 2) b[k--] = 0;
	}
}"
