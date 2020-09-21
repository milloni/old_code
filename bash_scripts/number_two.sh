#!/bin/bash

dirname=$1
if [[ -z "$dirname" ]]; then
    echo "Usage: $0 directory"
    exit 1
elif [[ ! -d "$dirname" ]]; then
    echo "Argument must be directory"
    exit 1
fi

echo $dirname

