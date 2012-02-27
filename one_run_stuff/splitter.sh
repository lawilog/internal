#!/bin/bash
echo -e "Name\tStrasse\tPLZ_Ort\tTel\tFax\teMail\tURL\tTyp"
n=0
while read x
do
#	echo "n=$n x=\"$x\""
	if [ -z "$x" ]
	then
		if [ $n -eq 4 ]
		then
			n=0
			echo -en "${data[0]}\t" # Name
			echo -en "${data[1]}\t" | sed 's/\, /\t/g' # Strasse PLZ_Ort
			echo -en "${data[2]}\t" | sed 's/Tel\.\: //g' | sed 's/\, Fax\: /\t/g' # Tel Fax
			echo -en "\t\t" # eMail URL
			echo "${data[3]}" # Typ
		elif [ $n -eq 5 ]
		then
			n=0
			echo -en "${data[0]}\t" # Name
			echo -en "${data[1]}\t" | sed 's/\, /\t/g' # Strasse PLZ_Ort
			echo -en "${data[2]}\t" | sed 's/Tel\.\: //g' | sed 's/\, Fax\: /\t/g' # Tel Fax
			echo -en "${data[3]}\t" | sed 's/ /\t/g' # eMail URL
			echo "${data[4]}" # Typ
		fi
	else
		data[$n]="$x"
		n=$[$n+1]
	fi
done
