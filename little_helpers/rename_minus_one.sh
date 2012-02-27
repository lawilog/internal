#!/bin/bash
x=$1
mv "$x" "${x:0:${#x}-1}"
