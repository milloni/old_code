#!/usr/bin/python
# Bubble sort

import json
import sys

def sort(a):
    n = len(a)
    h = 1
    while h < n / 3:
        h = 3 * h + 1
    while h > 0:
        for i in range(h, n):
            for j in range(i, h - 1, -h):
                if a[j] < a[j - h]:
                    a[j], a[j - h] = a[j - h], a[j]
                else:
                    break
        h /= 3

def main(argv):
    if len(argv) != 2:
        print "Usage: %s list_json" % (argv[0])
        sys.exit(1)
    a = json.loads(argv[1])
    sort(a)
    print a

if __name__ == '__main__':
    main(sys.argv)

