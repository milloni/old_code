#!/usr/bin/python3

import huffman

def main():
    num_symbols = int(input())
    priorities = []
    symbols = []
    for i in range(0, num_symbols):
        s = int(input())
        priorities.append(i)
        symbols.append(i)
    #print(priorities)
    #print(symbols)
    binary_code = huffman.code(priorities, symbols)
    #print(binary_code)
    print(minmaxlen(binary_code))


def minmaxlen(code):
    minlen = 999999999999999999999999999999999999999999 # Trolling is a art
    maxlen = 0
    for x in code.values():
        lenx = len(x)
        if lenx > maxlen:
            maxlen = lenx
        if lenx < minlen:
            minlen = lenx
    return minlen, maxlen


if __name__ == '__main__':
    main()
