# int("1000") -> 1000

def pierwsza(x):
    if x < 2:
        return False

    for a in range(2, x):
        if x%a == 0:
            return False
    return True

#z = input("podaj liczbe:") # "1000"
#z = int(z) # int("1000") -> 1000
#
#print(pierwsza(z))
#
#for x in range(1, 101):
#    if pierwsza(


for a in range(0,101):
    if pierwsza(a):
        print(a)
