#!/bin/bash

function func1 {
    echo "This message is from funcion 1"
}

function func2 {
    echo "This message is from funcion 2"
}

function func3 {
    echo "This message is from funcion 3"
}

echo -n "Enter a number: "
read number
if [[ -z "$number" ]]; then
    echo "must provide the number!"
    exit 1
elif [[ "$number" -lt 1 || "$number" -gt 3 ]]; then
    echo "number must be between 1 and 3"
    exit 1
fi

"func${number}"

