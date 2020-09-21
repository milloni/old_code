#!/bin/bash

word=$1
if [[ -z "$word" ]]; then
    echo "Usage: $0 word"
    exit 1
fi

asdf="${word}.${RANDOM}"
echo "$asdf"

