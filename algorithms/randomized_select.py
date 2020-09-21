#!/usr/bin/python

import json
import random
import sys

def _choose_pivot(a, lo, hi):
    return random.randint(lo, hi - 1)

def _partition(a, lo, hi):
    p = a[lo]
    i = lo + 1
    for j in range(i, hi):
        if a[j] < p:
            a[i], a[j] = a[j], a[i]
            i += 1
    a[lo], a[i - 1] = a[i - 1], a[lo]
    return i - 1

def _select(a, i, lo, hi):
    #print _select.__name__, i, lo, hi
    pi = _choose_pivot(a, lo, hi)
    a[lo], a[pi] = a[pi], a[lo]
    pi = _partition(a, lo, hi)
    if i == pi:
        return a[pi]
    elif i < pi:
        return _select(a, i, lo, pi)
    else:
        return _select(a, i, pi + 1, hi)

def select(a, i):
    # 0th order statistic is the smallest element, etc...
    return _select(a, i - 1, 0, len(a))

def proper_vocab(i):
    suffix = ""
    r = i % 10
    if   10 < i < 14: suffix = "th"
    elif r == 1:      suffix = "st"
    elif r == 2:      suffix = "nd"
    elif r == 3:      suffix = "rd"
    else:             suffix = "th"

    return "%d%s" % (i, suffix)

def main(argv):
    if len(argv) != 3:
        print "Usage: %s json_list index" % argv[0]
        sys.exit(1)
    a = json.loads(argv[1])
    i = int(argv[2])
    x = select(a, i)
    print "%s smallest element in array a is %d" % (proper_vocab(i), x)

if __name__ == '__main__':
    main(sys.argv)

