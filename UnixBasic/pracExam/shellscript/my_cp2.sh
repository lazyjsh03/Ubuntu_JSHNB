#! /bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <source_file> <destination_file>"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "The first argument must be a file."
    exit 1
fi

if [ -d "$2" ]; then
    cat "$1" > "$2/$(basename "$1")"
else
    cat "$1" > "$2"
fi