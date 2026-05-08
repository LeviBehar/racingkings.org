#!/bin/bash

CC="gcc"
ROOT=$(cd "$(dirname "$0")"/.. && pwd)
SOURCES=$(find "$ROOT" -name "*.c")
FLAGS="-Wall -g -fsyntax-only -c"

if [ -z "$SOURCES" ]; then
    echo "Error: No .c files found in $ROOT"
    exit 1
fi

echo "Compiling all .c files from: $ROOT"
echo "Flags: $FLAGS"

$CC $FLAGS $SOURCES

if [ $? -eq 0 ]; then
    echo "Status: SUCCESS"
else
    echo "Status: FAILURE"
    exit 1
fi
