#!/bin/bash
(mediainfo "$1"; echo Audio) | awk '
	BEGIN{
		L["English"]="en"; L["Bulgarian"]="bg"; L["Chinese"]="zh"; L["Croatian"]="hr"; L["Czech"]="cs"; L["Danish"]="da"; L["Dutch"]="nl"; L["English"]="en"; L["Finnish"]="fi"; L["French"]="fr"; L["German"]="de"; L["Greek"]="el"; L["Hebrew"]="he"; L["Hungarian"]="hu"; L["Indonesian"]="id"; L["Italian"]="it"; L["Japanese"]="ja"; L["Norwegian"]="no"; L["Polish"]="pl"; L["Portuguese"]="pt"; L["Romanian"]="ro"; L["Russian"]="ru"; L["Slovenian"]="sl"; L["Spanish"]="es"; L["Swedish"]="sv"; L["Turkish"]="tk"; L["Vietnamese"]="vi";
		lang=""
	}
	/^Language/{lang=($3 in L?L[$3]:$3)}
	/^Audio/{printf("%s\n", lang); lang="unk"}
	' | sort | uniq | tr '\n' ',' | sed 's/,$//'
echo
