#!/usr/bin/python

import sys

MAX_LINE = 80

def trans(c):
    if c in range(0, 0x20):
        return "0x20, "
    elif c in range(0x20, 0x7F):
        return "%#x, " % c
    elif c in range(0x7F, 0xFF):
        return "0x20, "


def main(argv):
    out = "db "
    ch_counter = 0
    for i in range(0, 0xFF):
        nxt = trans(i)
        out += nxt
        ch_counter += len(nxt)
        if ch_counter > MAX_LINE: 
            out = out[:-2] # trailing ", "
            out += '\ndb '
            ch_counter = 0
    out += '\n'
    sys.stdout.write(out)


if __name__ == "__main__":
    main(sys.argv[1:])

