#!/bin/sh
afl-fuzz -i input -o output -m 1024M -- ./bfci @@

