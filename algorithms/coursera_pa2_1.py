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
    #print [a[lo], a[mid], a[hi - 1]], a[median_of_three(a, lo, mid, hi - 1)]
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
    #print _sort.__name__, a, lo, hi
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
    g_count = 0
    _sort(a, 0, len(a))

def main(argv):
    a = []
    for line in sys.stdin:
        e = int(line)
        a.append(e)
    sort(a)
    print g_count

if __name__ == '__main__':
    main(sys.argv)

