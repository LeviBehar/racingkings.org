#!/bin/bash

CC="gcc"
OUTPUT="/tmp/racingkings.org_test"
ROOT=$(cd "$(dirname "$0")"/../.. && pwd)
SOURCES=$(find "$ROOT" -name "*.c")
FLAGS="-Wall -g"

if [ -z "$SOURCES" ]; then
    echo "Error: No .c files found in $ROOT"
    exit 1
fi

echo "Compiling all .c files from: $ROOT"
echo "Flags: $FLAGS"

$CC $FLAGS $SOURCES -o $OUTPUT -lm

if [ $? -eq 0 ]; then
    echo "Status: SUCCESS"
    echo "Output: $OUTPUT"
else
    echo "Status: FAILURE"
    exit 1
fi
