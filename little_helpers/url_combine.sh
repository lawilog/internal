#!/bin/bash
baseurl="$1"
relurl="$2"
if [ -z "$relurl" ]
then
	while read relurl; do $0 "$baseurl" "$relurl"; done
fi

if [ "${relurl:0:1}" == "/" ]
then
	x="${baseurl#*.*/}"
	# echo "x = $x"
	echo "${baseurl:0:$((${#baseurl} - ${#x}))}${relurl:1}"
elif (echo "$relurl" | egrep -q '^[A-Za-z0-9]*://') # [ "${relurl:0:4}" == "http" ]
then
	echo "${relurl}"
elif [ ! -z "${relurl}" ]
then
	echo "${baseurl%/*}/${relurl}"
fi
