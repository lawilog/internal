#!/bin/bash
if [ $# -ne 0 ]; then echo "$1" | $0; exit $?; fi
sed 's/\((.*)$\|$\)/\t\1/; s/\(--.*\t\|\t\)/\t\1/; s/\([[0-9]\+] *\t\|\t\)/\t\1/; s/\t-- */\t/; s/ *\t/\t/g'
