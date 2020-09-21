#!/bin/bash

f=non_existent_file

ls "$f" > /dev/null 2>&1
echo "$?"
touch "$f"
ls "$f" > /dev/null 2>&1
echo "$?"
rm "$f"

