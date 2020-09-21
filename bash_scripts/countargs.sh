#!/bin/bash

function countargs {
	echo "$#"
}

countargs "$*"
countargs "$@"

