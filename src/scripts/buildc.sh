#!/bin/bash

OUTPUT="/tmp/racingkings.org_build"
PROJECT_ROOT=$(cd "$(dirname "$0")"/../.. && pwd)
SOURCES=$(find "$PROJECT_ROOT" -name "*.c")

if [ -z "$SOURCES" ]; then
    echo "Error: No .c files found in $PROJECT_ROOT"
    exit 1
fi

echo "Compiling all files from: $PROJECT_ROOT"

gcc -Wall $SOURCES -o $OUTPUT -lm

if [ $? -eq 0 ]; then
    echo "-----------------------"
    echo "Build: SUCCESS"
    echo "Output: $OUTPUT"
    echo "-----------------------"
else
    echo "-----------------------"
    echo "Build: FAILURE"
    echo "-----------------------"
    exit 1
fi
