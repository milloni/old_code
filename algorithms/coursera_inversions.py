#!/usr/bin/python

from mergesort_inversions import count_inversions
import sys

def main(argv):
    l = []
    s = sys.stdin.readline()
    while s != '':
        l.append(int(s))
        s = sys.stdin.readline()
    count = count_inversions(l)
    print count

if __name__ == '__main__':
    main(sys.argv)

