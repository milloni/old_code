#!/usr/bin/python

import socket
import sys

address = "192.168.0.25"
ports = range(0, 1024)
ports_open = 1024 * [True]
for index, port in enumerate(ports):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((address, port))
    except socket.error as e:
        ports_open[index] = False
    if ports_open[index]:
        sys.stdout.write("P")
        # ABCD
    else:
        sys.stdout.write(".")
    sys.stdout.flush()
print("\nPORTS OPEN:")
print("===========")
for i, x in enumerate(ports_open):
    if x:
        print("tcp/{}".format(i))

