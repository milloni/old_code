#!/usr/bin/python

import json
import sys

def _merge(a, b):
    n = min(len(a), len(b))
    m = max(len(a), len(b))
    result = []
    j, k = 0, 0
    while j < len(a) and k < len(b):
        if a[j] < b[k]:
            result.append(a[j])
            j += 1
        else:
            result.append(b[k])
            k += 1
    
    # Only one of these should execute.
    while j < len(a):
        result.append(a[j])
        j += 1
    while k < len(b):
        result.append(b[k])
        k += 1
    
    return result
        
def _sort(a):
    if len(a) == 1:
        return a

    h = len(a) / 2
    a1 = _sort(a[:h])
    a2 = _sort(a[h:])
    return _merge(a1, a2)

def sort(a):
    return _sort(a)

def main(argv):
    if len(argv) != 2:
        print "Usage: %s list_json" % (argv[0])
        sys.exit(1)
    l = json.loads(argv[1])
    l = sort(l)
    print l

if __name__ == '__main__':
    main(sys.argv)

