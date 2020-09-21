#!/bin/bash

echo -n "str1: "
read str1
echo -n "str1: "
read str2

echo -n "Is str1 zero-length? "
if [[ -z "$str1" ]]; then
    echo "yes"
else
    echo "no"
fi

echo -n "Is str2 non-zero-length? "
if [[ -n "$str2" ]]; then
    echo "yes"
else
    echo "no"
fi

