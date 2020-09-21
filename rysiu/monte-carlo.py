import sys
import random




def na_kole(x, y):
    if x ** 2 + y ** 2 <= 1:
        return True
    return False
#a kwadrat plus be kwadrat <= 1


llocznek_pls = 0
liczba_punktow = int(sys.argv[1])
for i in range(0, liczba_punktow):
    x = random.random()
    y = random.random()
    if na_kole(x, y):
        llocznek_pls = llocznek_pls + 1

pi = 4 * llocznek_pls / liczba_punktow
print(pi)
