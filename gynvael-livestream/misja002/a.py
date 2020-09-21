#!/usr/bin/python

import base64

def mybin(x):
    return bin(x)[2:].zfill(8)

ct = """QW== QT== QT== QQ== QU== Qd== QU== Qd==
QX== QV== QW== Qe== QT== QR== QU== QT==
QT== QU== QX== QU== QT== QR== QT== QQ==
QW== Qe=="""

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

chunks = []
for x in ct.splitlines():
    chunks.extend(x.split())
chunks = [x[1] for x in chunks]

cnt = 0
result = ""
for i, x in enumerate(chunks):
    a = alphabet.index(x) & ((1 << 4) - 1)
    if i % 2 == 0:
        cnt += a << 4
    else:
        cnt += a
        #print mybin(cnt)
        result += chr(cnt)
        cnt = 0

print result

