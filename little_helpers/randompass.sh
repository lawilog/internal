#!/bin/bash
cat /dev/urandom | tr -cd '[[:alnum:]]!#$%&()*+,-./:;<=>?@[\]^_{|}' | fold -w8 | head -n 10
