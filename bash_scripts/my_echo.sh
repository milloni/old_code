#!/bin/bash

function my_echo {
	my_var="value of my_var"
	local my_local_var="value of my_local_var"

	echo "$my_var"
	echo "$my_local_var"
	echo "$0"
	echo "$1"
	echo "$2"
	echo "$*"
	echo "$@"
	echo "$#"
}

my_echo foo bar
type my_echo
echo

type gdb
echo

echo "$my_var"
echo "$my_local_var"

