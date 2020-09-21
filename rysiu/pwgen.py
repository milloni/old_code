#!/usr/bin/python3

import random

haslo = ""
dlugosc = 8
for licznik in range(0, dlugosc):
    wylosowany_znak = chr(random.randint(ord('!'), ord('~')))
    wylosowany_string = str(wylosowany_znak)
    haslo += wylosowany_znak
print(haslo)
