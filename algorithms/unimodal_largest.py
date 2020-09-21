#!/usr/bin/python
# Input:  unimodal array A, that is an array whose elements are increasing
#         order up until its maximum element, after which its elements are
#         in decreasing order
# Output: maximum element of A

import json
import sys

def find_maximum(a):
    n = len(a)
    h = n / 2
    while True:
        if a[h - 1] < a[h] > a[h + 1]:
            return a[h]
        elif a[h - 1] > a[h] > a[h + 1]:
            h /= 2
        elif a[h - 1] < a[h] < a[h + 1]:
            h += h / 2
        else:
            raise StandardError("oops")

def main(argv):
    if len(argv) != 2:
        print "Usage: %s json_list" % (argv[0])
        sys.exit(1)
    a = json.loads(argv[1])
    maximum = find_maximum(a)
    print maximum

if __name__ == '__main__':
    main(sys.argv)

