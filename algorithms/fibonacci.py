#!/usr/bin/python

import sys

def fib(n):
    k = 0
    l = 1
    r = k + l
    for i in range(0, n):
        
        
    return r

def main(argv):
    if len(argv) != 2:
        print "Usage: %s n" % (argv[0])
        sys.exit(1)
    n = int(argv[1])
    f = fib(n)
    print f

if __name__ == '__main__':
    main(sys.argv)

