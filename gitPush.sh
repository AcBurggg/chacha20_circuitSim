#!/bin/bash
if [ -z "$1" ]; then
	echo "Usage: $0 \"commit message \""
	exit 1
fi
git add -A
git commit -m "$1"
git push
