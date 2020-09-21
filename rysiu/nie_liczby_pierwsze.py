#!/usr/bin/python3

def foo():
    print("Rzeczy do wypisania:")

def powierzchnia(x, y):
    return x * y

# input(tekst) -> to co uzytkownik poda
# nazwazmiennej = wartos
x = int(input("pierwszy bok prostokątu: "))
y = int(input("drugi bok prostokątu: "))
pole = powierzchnia(x, y)
print(pole)

