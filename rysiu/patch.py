#!/usr/bin/python3

import sys

def main():
    diff_path = sys.argv[1]
    with open(diff_path) as f:
        diff = f.read()
    print(diff)

if __name__ == '__main__':
    main()
