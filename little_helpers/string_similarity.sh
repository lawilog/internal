#!/bin/bash
verbose=0
printmode="a<b?a:b"
cmpmode="w"
while [[ $# > 0 ]]
do
	case "$1" in
	-h|--help)
		echo -e "$0 [options] \"string A\" \"string B\"\n" \
			"options are:\n\n" \
			"-h|--help: print this help\n\n" \
			"compare modes [default: -byword]:\n" \
			"-byword: use wdiff to compare strings word by word\n" \
			"-bychar: use diff to compare strings character by character\n\n" \
			"print modes [default: -min]:\n" \
			"-A: print percentage of (words or characters) in string A that are also in string B\n" \
			"-B: print percentage of (words or characters) in string B that are also in string A\n" \
			"-min, -max, -avg: print minimum, maximum or average of -A and -B values"
		exit 0
	;;
	
	-v)
		verbose=1
		shift
	;;
	
	-min)
		printmode="a<b?a:b"
		shift
	;;
	
	-A)
		printmode="a"
		shift
	;;
	
	-B)
		printmode="b"
		shift
	;;
	
	-avg)
		printmode="(a+b)/2"
		shift
	;;
	
	-max)
		printmode="a>b?a:b"
		shift
	;;
	
	-byword)
		cmpmode="w"
		shift
	;;
	
	-bychar)
		cmpmode="d"
		shift
	;;
	
	*)
		break
	;;
	
	esac
done

fa=$(tempfile)
fb=$(tempfile)
if [ "$cmpmode" = "w" ]
then
	echo "$1" > "$fa"
	echo "$2" > "$fb"
	outp=$(LC_ALL="C"  wdiff -si "$fa" "$fb")
	test $verbose -eq 1 && echo "$outp"
	echo "$outp" | tail -2 | awk "{if(x++) b=1*\$5; else a=1*\$5;} END{printf(\"%i\\n\", $printmode)}"
else
	echo "$1" | sed 's/\(.\)/\1\n/g' > "$fa"
	echo "$2" | sed 's/\(.\)/\1\n/g' > "$fb"
	outp=$(diff -di "$fa" "$fb" | egrep '^<|^>')
	test $verbose -eq 1 && echo "$outp"
	echo $(echo "$outp" | egrep '^<' | wc -l) $(echo "$outp" | egrep '^>' | wc -l) $(cat "$fa" | wc -l) $(cat "$fb" | wc -l) | awk "{a=\$3==1?0:100*(1-\$1/(\$3-1)); b=\$4==1?0:100*(1-\$2/(\$4-1)); printf(\"%i\\n\", $printmode)}"
fi
rm "$fa" "$fb"
