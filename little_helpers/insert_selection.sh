#!/bin/bash
test -z "$1" && del="\\D1" || del=""
xvkbd -no-jump-pointer -xsendevent -text "${del}`xsel`" 2>/dev/null
