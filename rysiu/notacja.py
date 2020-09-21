def can_be_int(x):
    try:
        int(x)
    except:
        return False
    return True


# 2 3 + 5 -
pojebananotacja = input("wpisz tu: ")
kappa = pojebananotacja.split()
liczbowalista = []
for x in kappa:
    if x == "+":
        liczbowalista.append(liczbowalista.pop() + liczbowalista.pop())
    elif x == "-" or x == "−":
        liczbowalista.append(liczbowalista.pop() - liczbowalista.pop())
    elif x == "/" or x == "÷":
        liczbowalista.append(liczbowalista.pop() / liczbowalista.pop())
    elif x == "*" or x == "×":
        liczbowalista.append(liczbowalista.pop() * liczbowalista.pop())
    else:
        liczbowalista.append(int(x))

w = liczbowalista[-1]
if int(w) == w:
    print(int(w))
else:
    print(w)
