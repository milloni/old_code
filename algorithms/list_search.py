#!/usr/bin/python

import json
import mergesort
import sys

def _search(a, e):
    n = len(a)
    h = n / 2
    if a[h] == e:
         return True
    elif n == 1:
         return False
    elif a[h] > e:
         return _search(a[:h], e)
    else:
         return _search(a[h:], e)

def search(a, e):
    a = mergesort.sort(a)
    return _search(a, e)

def main(argv):
    if len(argv) != 3:
        print "Usage: %s list_to_search_json element_to_find" % (argv[0])
        sys.exit(1)
    a = json.loads(argv[1])
    e = int(argv[2])
    if search(a, e):
        print "%d is in the array" % (e)
    else:
        print "%d is not in the array" % (e)

if __name__ == '__main__':
    main(sys.argv)

