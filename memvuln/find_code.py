#/usr/bin/env python3

import sys

what = bytes.fromhex(sys.argv[1].lstrip("0x"))
path = sys.argv[2]
with open(path, "rb") as f:
    where = f.read()
print(hex(where.find(what)))
