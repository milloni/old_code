#!/usr/bin/python

import sys

def hamming_distance(a, b):
    result = 0
    for x, y in zip(a, b):
        if x != y:
            result += 1
    return result

def min_hamming_distance(data):
    result = 0xFFFFFFFF # is there a better way?
    for x in data:
        for y in data:
            if x != y:
                d = hamming_distance(x, y)
                if d < result:
                    result = d
                #result = (d < result) ? (d) : (result)
    return result

def main(argv):
    if argv < 2:
        sys.stdout.write("Usage: min_hamming_distance.py list-of-bitstrings\n")
        sys.exit(1)
    sys.stdout.write("%d\n" % min_hamming_distance(argv[1:]))

if __name__ == '__main__':
    main(sys.argv)

