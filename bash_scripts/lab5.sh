#!/bin/bash

opr=$1
first=$2
second=$3

if [[ -z "$opr" || -z "$first" || -z "$second" ]]; then
    echo "Usage: $0 operator first_argument second_argument"
    echo "  operator: one of the following: a, s, m, d"
    echo "  first_argument, second_argument: numbers being used as arguments"
    echo "                                   to the operator"
    exit 1
fi

if [[ "$opr" != 'a' && "$opr" != 's' && "$opr" != 'm' && "$opr" != 'd' ]]; then
    echo "operator must be one of the following: a, s, m, d"
    exit 1
fi

case "$opr" in
    a) result=$((first + second)) ;;
    s) result=$((first - second)) ;;
    m) result=$((first * second)) ;;
    d) result=$((first / second)) ;;
esac
echo "$result"

