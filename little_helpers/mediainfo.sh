#!/bin/bash
mediainfo "${@}" | egrep '^Video|^Audio|^Text|File size|Duration|Codec ID|Bit rate|Width|Height|Language|Title' | awk '/:/{gsub(/ *:/, ":", $0); printf(" | %s", $0)}; !/:/{printf("\n%s\t", $0)} END{printf "\n"}'
