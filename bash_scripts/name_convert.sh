#!/bin/bash

function fatal_error {
     echo "$1"
     exit 1
}

fname=$1
[[ -n "$fname" ]] || fatal_error "Usage: $0 fname"
[[ $fname == *.pcx ]] || fatal_error "fname must end with pcx"

echo "$fname"
echo "${fname%.pcx}.jpg"

