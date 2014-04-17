#!/bin/bash
p=$(echo | align_as_table &> /dev/null && echo align_as_table || echo cat)
$p "$@"
