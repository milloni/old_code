#!/usr/bin/python

import json
import sys

def _sort_count(a):
    if len(a) == 1:
        return (0, a)
    
    h = len(a) / 2
    count_b, b = _sort_count(a[:h])
    count_c, c = _sort_count(a[h:])
    count_split, d = _merge_count_split(b, c)
    return count_b + count_c + count_split, d

def _merge_count_split(a, b):
    count = 0
    result = []
    i, j = 0, 0
    while i < len(a) and j < len(b):
        if a[i] > b[j]:
            result.append(b[j])
            j += 1
            count += len(a) - i
        else:
            result.append(a[i])
            i += 1

    # Only one of these should execute
    while i < len(a):
        result.append(a[i])
        i += 1
    while j < len(b):
        result.append(b[j])
        j += 1
    
    return count, result

def count_inversions(a):
    count, srtd = _sort_count(a)
    return count

def main(argv):
    if len(argv) != 2:
        print "Usage: %s list_json" % (argv[0])
        sys.exit(1)
    a = json.loads(argv[1])
    count = count_inversions(a)
    print count

if __name__ == '__main__':
    main(sys.argv)

