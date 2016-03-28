#!/bin/bash
uhrzeit="$(date +"Es ist %A, der %_d %B um %_H Uhr %M." | awk 'BEGIN{
	a[1]="erste";
	a[2]="zweite";
	a[3]="dritte";
	a[4]="vierte";
	a[5]="fünfte";
	a[6]="sechste";
	a[7]="siebente";
	a[8]="achte";
	a[9]="neunte";
	a[10]="zehnte";
	a[11]="elfte";
	a[12]="zwölfte";
	a[13]="dreizehnte";
	a[14]="vierzehnte";
	a[15]="fünfzehnte";
	a[16]="sechszehnte";
	a[17]="siebzehnte";
	a[18]="achtzehnte";
	a[19]="neunzehnte";
	a[20]="zwanzigste";
	a[21]="einundzwanzigste";
	a[22]="zweiundzwanzigste";
	a[23]="dreizwanzigste";
	a[24]="vierundzwanzigste";
	a[25]="fünfundzwanzigste";
	a[26]="sechsundzwangzigste";
	a[27]="siebenundzwangzigste";
	a[28]="achtundzwangzigste";
	a[29]="neunundzwangzigste";
	a[30]="dreißigste";
	a[31]="einunddreißigste";
} {gsub(/.*/, a[$5], $5); print}')"

tmpf=$(tempfile)
curl -s "http://wttr.in/ilmenau" -o "$tmpf"
if (sed -n 12p "$tmpf" | grep -qi rain)
then
	regen="Regen erwartet."
else
	regen="Kein Regen."
fi
T=$(cat "$tmpf" | sed -r "s/\x1B\[([0-9]{1,3}((;[0-9]{1,3})*)?)?[m|K]//g" | sed -n '13s/[^0-9│–]//g; 13s/[│–]/ /gp' | awk 'BEGIN{min=999; max=-999} {for(i=1;i<=6;++i) {if($i<min) min=$i; if($i>max) max=$i}} END{print "Prognose: Zwischen", min, "und", max, "Grad Celsius."}')

# echo "$uhrzeit $T $regen"
echo "$uhrzeit $T $regen" | espeak -vmb-de5 -b1
rm "$tmpf"

