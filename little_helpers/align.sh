#!/bin/bash
export PATH=${HOME}/gcc-4.8.2/bin:$PATH
export LD_LIBRARY_PATH="${HOME}/gcc-4.8.2/lib64:$LD_LIBRARY_PATH"

p=$(echo | align_as_table &> /dev/null && echo align_as_table || echo cat)
$p "$@"
