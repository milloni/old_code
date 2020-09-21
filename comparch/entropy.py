#!/usr/bin/python

import json
import sys
from math import log

def entropy(data):
    result = 0
    for x in data:
        result += (-1.0) * x * log(x, 2)
    return result

def parse_input(argv):
    argv = argv[1:]
    s = ''.join(x for x in argv)
    data = json.loads(s)
    return data

def main(argv):
    if len(argv) < 2:
        sys.stdout.write("Usage: entropy.py list-of-entries\n")
        sys.exit(1)
    data = parse_input(argv)
    ent = entropy(data)
    sys.stdout.write("%f\n" % ent)

if __name__ == '__main__':
    main(sys.argv)

