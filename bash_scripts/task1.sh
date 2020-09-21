#!/bin/bash

# Arguments
f=${1:?"Filename missing."}
n=${2:-3}
sed '/^$/d' < "$f" | sort -nr | head -n "$n"

