#!/bin/bash
(test -z "$1" && sed 's/<a/\n&/g' || sed 's/<a/\n&/g' "$1") | sed -n "/[Hh][Rr][Ee][Ff]/ s/.*[Hh][Rr][Ee][Ff] *= *['\"]\([^'\"]*\)['\"].*/\1/gp"
