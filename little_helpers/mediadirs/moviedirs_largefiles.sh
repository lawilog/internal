#!/bin/bash
for dir in "$@"
do
	find -L "$dir" -size +350M -exec dirname {} \; | sed -r 's#/(VIDEO_TS|video_ts|STREAM|CD1|CD2)$##g' | uniq
done
