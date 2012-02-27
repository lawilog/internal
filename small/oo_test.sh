#!/bin/bash

LANGS1="af ar as_IN be_BY bg bn br brx bs ca cs cy da de dgo dz el en_GB en_ZA eo es et eu fa fi fr ga gl gu he hi_IN hr hu id it ja ka kk km kn_IN ko kok ks ku lt mai mk ml_IN mn mni mr_IN nb ne nl nn nr ns oc or_IN pa_IN pl pt pt_BR ru rw sa_IN sat sd sh sk sl sr ss st sv sw_TZ ta ta_IN te_IN tg th ti_ER tn tr ts uk ur_IN uz ve vi xh zh_CN zh_TW zu"
LANGS="${LANGS1} en en_US"

# app-dicts/myspell-* dictionaries
SPELL_DIRS="af bg ca cs cy da de el en eo es et fo fr ga gl he hr hu ia id it ku lt lv mi mk ms nb nl nn pl pt ro ru sk sl sv sw tn uk zu"
SPELL_DIRS_DEPEND=""

for X in ${LANGS} ; do
	IUSE="${IUSE} linguas_${X}"
	LINGUA_LANG=${X:0:2}
	for Y in ${SPELL_DIRS}; do
		if [ "${Y}" == "${LINGUA_LANG}" ]
		then
			SPELL_DIRS_DEPEND="${SPELL_DIRS_DEPEND} linguas_${X}? ( app-dicts/myspell-${Y} )"
		fi
	done
done

echo ${SPELL_DIRS_DEPEND}
