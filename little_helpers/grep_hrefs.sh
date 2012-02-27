#!/bin/bash
sed 's/<a/\n&/g' "$1" | sed -n "/href/ s/.*href=['\"]\([^'\"]*\)['\"].*/\1/gp"
