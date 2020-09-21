#!/usr/bin/python2

import sys

# To jest liczba xd
a=int(sys.argv[1])

for x in range(2, a):
    if a % x == 0:
        print "Ta liczba nie jest pierwsza"
        sys.exit(0)

print "Ta liczba jest pierwsza"

