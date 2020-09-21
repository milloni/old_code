#!/usr/bin/python

import math
import sys

counter = 0

def karatsuba(x, y):
    global counter
    n = max(len(str(x)), len(str(y)))
    xs = str(x).zfill(n)
    ys = str(y).zfill(n)
    print "CALL", xs, ys

    if n == 1:
        print "%s %s --> %d" % (xs, ys, x * y)
        return x * y

    h = n / 2;
    a = int(xs[:h])
    b = int(xs[h:])
    c = int(ys[:h])
    d = int(ys[h:])
    z1 = karatsuba(a, c)
    z2 = karatsuba(b, d)
    z3 = karatsuba(a + b, c + d) - z2 - z1
    print "counter: %d" % (counter)
    counter += 1
    hm = int(math.ceil(n / 2.0))
    result = (10 ** n) * z1 + (10 ** hm) * z3 + z2
    print "%s %s --> %d" % (xs, ys, result)
    return result
def main(argv):
    if len(argv) != 3:
        print "Usage: %s first_arg second_arg" % (argv[0])
        sys.exit(1)
    x = int(argv[1])
    y = int(argv[2])
    z = karatsuba(x, y)
    print z

if __name__ == '__main__':
    main(sys.argv)

