def prime(n):
    for z in range(2, n):
        if n % z == 0:
            return False
    return True
    

for x in range(2, 101):
    if prime(x):
        print(x)
