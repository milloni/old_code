#!/usr/bin/python
# Selection sort

import json
import sys

def sort(a):
    for i in range(0, len(a)):
        imin = i
        for j in range(i + 1, len(a)):
            if a[j] < a[imin]:
                imin = j
        a[i], a[imin] = a[imin], a[i]

def main(argv):
    if len(argv) != 2:
        print "Usage: %s list_json" % (argv[0])
        sys.exit(1)
    a = json.loads(argv[1])
    sort(a)
    print a

if __name__ == '__main__':
    main(sys.argv)

