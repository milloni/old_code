#!/bin/bash

# Banner
if [[ -z "$1" ]]; then
	echo "Usage: ./build.sh [options] outfile"
	echo "Options summary:"
	echo "	-g,  build with debugger symbols."
	exit 1
fi

# Options
CC="gcc"
CFLAGS="-Wall -pedantic -m32"

# Parse commandline options
OPT=""
while getopts "g" OPT; do
	case "$OPT" in
		g)
			CFLAGS="$CFLAGS -ggdb"
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			;;
	esac
done
shift $((OPTIND - 1))

# Is cmdline argument a source file or an output file?
if [[ "$1" == *.c ]]; then
	SRC="$1"
	OUT=${SRC%.*}
else
	OUT="$1"
	SRC="$OUT.c"
fi

# Do the build
$CC $CFLAGS -o "$OUT" "$SRC"

