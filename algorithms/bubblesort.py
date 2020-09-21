#!/usr/bin/python
# Bubble sort

import json
import sys

def sort(a):
    n = len(a)
    for i in range(0, n):
        for j in range(1, n - i):
            if a[j - 1] > a[j]:
                a[j - 1], a[j] = a[j], a[j -1]

def main(argv):
    if len(argv) != 2:
        print "Usage: %s list_json" % (argv[0])
        sys.exit(1)
    a = json.loads(argv[1])
    sort(a)
    print a

if __name__ == '__main__':
    main(sys.argv)

