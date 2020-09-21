import subprocess
import sys

for x in range(-200000, 200000):
    if x % 1000 == 0:
        print(x)
    xstr = str(x)
    result = subprocess.getoutput("./int_to_string " + xstr)
    if result != xstr:
        print("WRONG", x)
        sys.exit(1)
print("PASS")
