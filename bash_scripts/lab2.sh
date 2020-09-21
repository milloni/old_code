#!/bin/bash

dirname="$1"
if [[ -z "$dirname" ]]; then
    echo "Usage: $0 dirname"
    exit 1
elif [[ -d "$dirname" ]]; then
    echo "$dirname already exists!"
    exit 1
fi

mkdir "$dirname"
cd "$dirname"
echo "You are here: $(pwd)"
cd -
rmdir "$dirname"

