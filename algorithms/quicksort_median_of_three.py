#!/usr/bin/python

import json
import random
import sys

g_count = 0

def median_of_three(a, xi, yi, zi):
    if   a[xi] <= a[yi] <= a[zi] or a[zi] <= a[yi] <= a[xi]: return yi
    elif a[yi] <= a[zi] <= a[xi] or a[xi] <= a[zi] <= a[yi]: return zi
    elif a[zi] <= a[xi] <= a[yi] or a[yi] <= a[xi] <= a[zi]: return xi
    else:                                                    raise RuntimeError()

def _choose_pivot(a, lo, hi):
    mid = lo + (hi - lo - 1) / 2
    return median_of_three(a, lo, mid, hi - 1)

def _partition(a, lo, hi):
    p = a[lo]
    i = lo + 1
    for j in range(i, hi):
        if a[j] < p:
            a[i], a[j] = a[j], a[i]
            i += 1
    a[lo], a[i - 1] = a[i - 1], a[lo]
    return i - 1

def _sort(a, lo, hi):
    global g_count
    g_count += hi - lo - 1
    if hi - lo == 1:
        return
    #elif hi - lo == 2:
    #    small = min(a[lo], a[hi - 1])
    #    big = max(a[lo], a[hi - 1])
    #    a[lo] = small
    #    a[hi - 1] = big
    #    return

    pi = _choose_pivot(a, lo, hi)
    a[lo], a[pi] = a[pi], a[lo]
    pi = _partition(a, lo, hi)
    if pi > lo:     _sort(a, lo, pi)
    if pi < hi - 1: _sort(a, pi + 1, hi)

def sort(a):
    _sort(a, 0, len(a))

def main(argv):
    if len(argv) != 2:
        print "Usage: %s json_list" % argv[0]
        sys.exit(1)
    a = json.loads(argv[1])
    sort(a)
    print a

if __name__ == '__main__':
    main(sys.argv)

