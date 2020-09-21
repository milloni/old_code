#!/bin/bash

for i in {1..60}; do
    output=$(./circular-buffer 2>&1)
    echo "$output" | grep -q logic_error
    if [[ "$?" = 0 ]]; then
        echo "$output"
        exit 0
    fi
done

