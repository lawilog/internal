#!/bin/bash
(for ext in c C cpp h hpp php; do find -type f -name \*.${ext}; done ) | while read x; do grep -Hn $@ $x; done
